import uuid
import re

from src.communication.latin import Latin
from src.communication.cipher import Cipher


class Messages(object):
    """
    This class handles sending and receiving messages using encryption.
    """
    def __init__(self, cipher: Cipher, id_nbr: str, language: Latin) -> None:
        """
        Initialize a Messages instance with a cipher and an ID number.
        """
        self.uuid_used: list[str] = ["",]
        self.id: str = id_nbr
        self.cipher: Cipher = cipher
        self.language: Latin = language
        self.msg: str = 'Broadcast "'

    def send_coord(self, message: str, pos: (int, int)) -> str:
        new_uuid: str = ""
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

    def validate_inventory_pattern(self, s):
        pattern = r'^\[\s*food\s+\d+,\s+linemate\s+\d+,\s+deraumere\s+\d+,\s+sibur\s+\d+,\s+mendiane\s+\d+,\s+phiras\s+\d+,\s+thystame\s+\d+\s*\]$'
        return 1 if re.match(pattern, s) else 0

    def validate_encryption_pattern(self, s):
        pattern = r'^(?:\d+#){9}\d+(?:#(?:\d+#){9}\d+)*$'
        return 0 if re.fullmatch(pattern, s) else 1

    def validate_look_pattern(self, s):
        pattern = r'^\[ player.*\]$'
        return 1 if re.match(pattern, s) else 0

    def receive(self, message: str) -> str | list[dict[str, str | int | tuple[int, int]]]:
        """
        Receive and process encrypted messages.

        Parameters:
            message (str): The encrypted message to be processed.

        Returns:
            str | list[dict[str, str | int | tuple[int, int]]]: Either the processed message or a list of dictionaries containing message details.
        """
        if self.validate_inventory_pattern(message):
            return message
        if self.validate_look_pattern(message):
            return message
        if message == 'ok\n' or message == 'ko\n':
            return message
        match = re.search(r'\d+, ', message)
        result: list[dict[str, str | int]] = []
        if match and len(message) > 4:
            messages = message[match.end() + 1:-2]
            messages = messages.split('|')
            for msg in messages:
                parts = msg.split()
                if parts[0] != 'ACCMST' or parts[2] in self.uuid_used or self.validate_encryption_pattern(parts[3]):
                    return 'ko'
                self.uuid_used.append(parts[2])
                text = parts[3].split('#')
                text = self.cipher.decryption([int(i) for i in text])
                text = text.split('#')
                if text[0] in self.language.verbum.values():
                    result.append({
                        'id': int(parts[1]),
                        'msg': text[0],
                        **({'coord': tuple(map(int, text[1].split(',')))} if len(text) > 1 else {})
                    })
                else:
                    result.append({'id': 0, 'msg': 'ko'})

        return result

    def buf_messages(self, message: str, receiver_id: int = 0, coord: tuple[int, int] = None) -> None:
        if coord is None:
            self.buf_msg_without_coord(message, receiver_id)
        else:
            self.buf_msg_coord(message, receiver_id, coord)

    def buf_msg_without_coord(self, message: str, receiver_id: int) -> None:
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

    def buf_msg_coord(self, message: str, receiver_id: int, pos: (int, int)) -> None:
        new_uuid: str = ""
        while new_uuid in self.uuid_used:
            new_uuid = uuid.uuid4().__str__()
        if new_uuid not in self.uuid_used:
            self.uuid_used.append(new_uuid)
        message += f'#{pos[0]},{pos[1]}'
        encrypted_msg = self.cipher.encryption(message)
        if self.msg == 'Broadcast "':
            self.msg += f'ACCMST {receiver_id} {new_uuid} {encrypted_msg}'
        else:
            self.msg += f'|ACCMST {receiver_id} {new_uuid} {encrypted_msg}'

    def send_buf(self) -> str:
        self.msg += '"'
        return self.msg
