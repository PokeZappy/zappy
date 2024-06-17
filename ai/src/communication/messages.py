import uuid
import re

from ai.src.communication.latin import Latin
from ai.src.communication.cipher import Cipher
from ai.src.utils.messages import validate_look_pattern, validate_encryption_pattern, validate_inventory_pattern, get_infos, exctrat_direction


class Messages(object):
    """
    This class handles sending and receiving messages using encryption.
    """
    def __init__(self, cipher: Cipher, id_nbr: str, language: Latin, debug: bool = False) -> None:
        """
        Initialize a Messages instance with a cipher and an ID number.
        """
        self.uuid_used: list[str] = ["", ]
        self.id: str = id_nbr
        self.cipher: Cipher = cipher
        self.language: Latin = language
        self.msg: str = 'Broadcast "'
        self.debug: bool = debug

    def send_coord(self, message: str, pos: (int, int)) -> str:
        new_uuid: str = ''
        while new_uuid in self.uuid_used:
            new_uuid = uuid.uuid4().__str__()
        if new_uuid not in self.uuid_used:
            self.uuid_used.append(new_uuid)
        message += f'#{pos[0]},{pos[1]}'
        encrypted_msg = self.cipher.encryption(message)
        return f'Broadcast "ACCMST {self.id} {new_uuid} {encrypted_msg}"'

    def send(self, message: str) -> str:
        """
        Send an encrypted message.

        Parameters:
            message (str): The message to be sent.

        Returns:
            str: A formatted string representing the broadcast message.
        """
        new_uuid: str = ""
        while new_uuid in self.uuid_used:
            new_uuid = uuid.uuid4().__str__()
        if new_uuid not in self.uuid_used:
            self.uuid_used.append(new_uuid)
        encrypted_msg = self.cipher.encryption(message)
        return f'Broadcast "ACCMST {self.id} {new_uuid} {encrypted_msg}"'

    def receive(self, message: str, action: any = None) -> tuple[str, str | list[dict[str, str | int | tuple[int, int]]]]:
        """
        Receive and process encrypted messages.

        Parameters:
            message (str): The encrypted message to be processed.
            action (any):

        Returns:
            str | list[dict[str, str | int | tuple[int, int]]]: Either the processed message or a list of dictionaries containing message details.
        """
        if validate_inventory_pattern(message):
            return 'inventory', message
        if validate_look_pattern(message):
            return 'look', message
        if message == 'ok\n':
            if self.debug:
                print(f'ok: {action}')
            return 'ok', action
        if message == 'ko\n':
            if self.debug:
                print(f'ko: {action}')
            return 'ko', action
        return self.broadcast_received(message)

    def broadcast_received(self, message: str) -> tuple[str, str | list[dict[str, str | int | tuple[int, int]]]]:
        """
        Process the received broadcast message and extract relevant information.

        Parameters:
            message (str): The encrypted message received.

        Returns:
            tuple[str, str | list[dict[str, str | int | tuple[int, int]]]]: A tuple containing the status of the broadcast and the processed message details.
        """
        save_msg: str = message
        match = re.search(r'\d+, ', message)
        result: list[dict[str, str | int]] = []
        if match and len(message) > 4:
            messages = message[match.end() + 1:-2]
            messages = messages.split('|')
            for msg in messages:
                parts = msg.split()
                if parts[0] != 'ACCMST' or parts[2] in self.uuid_used or validate_encryption_pattern(parts[3]):
                    return 'broadcast', [{'id': 0, 'msg': 'ko'}]
                self.uuid_used.append(parts[2])
                text = parts[3].split('#')
                text = self.cipher.decryption([int(i) for i in text])
                text = text.split('#')
                if text[0] == 'est dominus aquilonis':

                    direction = exctrat_direction(save_msg)
                    result.append({
                        'id': int(parts[1]),
                        'msg': text[0],
                        'direction': direction
                    })
                elif text[0] in self.language.verbum.values():
                    infos, nbr = get_infos(text)
                    result.append({
                        'id': int(parts[1]),
                        'msg': text[0],
                        **({'coord': tuple(map(int, text[1].split(',')))} if len(text) > 1 and text[
                            1][0].isnumeric() else {}),
                        **({'infos': list(infos)} if infos is not None else {}),
                        **({'nbr': list(nbr)} if infos is not None else {})
                    })
                else:
                    result.append({'id': 0, 'msg': 'ko'})
        print(result)
        return 'broadcast', result

    def buf_messages(self, message: str, receiver_id: int = 0, coord: tuple[int, int] = None,
                     infos: list[list[str, str]] = None) -> None:
        """
        Append a message to the buffer for broadcasting.

        Parameters:
            message (str): The message to be sent.
            receiver_id (int): The ID of the message receiver.
            coord (tuple[int, int], optional): The coordinates associated with the message. Defaults to None.
            infos (list[str, str], optional): Additional information to be included in the message. Defaults to None.
        """
        if coord is not None:
            message += f'#{coord[0]},{coord[1]}'
        if infos is not None:
            message += f'#{'~'.join(';'.join(info) for info in infos)}'
        self.buf_msg_default(message, receiver_id)

    def buf_msg_default(self, message: str, receiver_id: int) -> None:
        """
        Append an encrypted message to the buffer for broadcasting.

        Parameters:
            message (str): The message to be encrypted and sent.
            receiver_id (int): The ID of the message receiver.
        """
        new_uuid: str = ""
        while new_uuid in self.uuid_used:
            new_uuid = uuid.uuid4().__str__()
        if new_uuid not in self.uuid_used:
            self.uuid_used.append(new_uuid)
        encrypted_msg = self.cipher.encryption(message)
        if self.msg == 'Broadcast "':
            self.msg += f'ACCMST {receiver_id} {new_uuid} {encrypted_msg}'
        else:
            self.msg += f'|ACCMST {receiver_id} {new_uuid} {encrypted_msg}'

    def send_buf(self) -> str:
        """
        Send the buffered messages as a formatted broadcast message.

        Returns:
            str: A formatted string representing the broadcast message.
        """
        result = self.msg + '"'
        self.msg = 'Broadcast "'
        return result



