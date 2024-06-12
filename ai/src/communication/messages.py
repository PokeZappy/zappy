import uuid
import re

from src.communication.latin import Latin
from src.communication.cipher import Cipher


class Messages(object):
    """
    This class handles sending and receiving messages using encryption.
    """
    def __init__(self, cipher: Cipher, id_nbr: str, language: Latin):
        """
        Initialize a Messages instance with a cipher and an ID number.
        """
        self.uuid_used: list[str] = ["",]
        self.id: str = id_nbr
        self.cipher: Cipher = cipher
        self.language: Latin = language

    def send_coord(self, message: str, pos: (int, int)):
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

    def receive(self, message: str) -> str | list[str]:
        """
        Receive and decrypt a message.

        Parameters:
            message (str): The received message.

        Returns:
            str: The decrypted message.
             list[str]: The decrypted message and the coords
        """
        match = re.search(r'\d+, ', message)
        if match and len(message) > 4:
            message = message[match.end() + 1:-2]
            parts = message.split()
            if parts[0] != 'ACCMST' or parts[2] in self.uuid_used:
                # TODO - revoir look inventory pour qu'il passe la sécurité mais pas le reste
                return message
            self.uuid_used.append(parts[2])
            message = parts[3].split('#')
            message = self.cipher.decryption([int(i) for i in message])
            message = message.split('#')
            if message[0] in self.language.verbum.values():
                return message if len(message) > 1 else message[0]
            else:
                return 'ko'
        return message
