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

    def receive(self, message: str) -> str:
        """
        Receive and decrypt a message.

        Parameters:
            message (str): The received message.

        Returns:
            str: The decrypted message.
        """
        match = re.search(r'\d+, ', message)
        if match and len(message) > 4:
            message = message[match.end() + 1:-2]
            words = message.split()
            if words[0] != 'ACCMST' or words[2] in self.uuid_used:
                return 'ko'
            self.uuid_used.append(words[2])
            message = words[3].split('#')
            message = self.cipher.decryption([int(i) for i in message])
            if message in self.language.verbum.values():
                return message
            else:
                return 'ko'
        return message
