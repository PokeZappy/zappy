import uuid
import pytest

from src.communication.cipher import Cipher
from src.communication.messages import Messages
from src.communication.latin import Latin


class TestMessages:

    #  send method generates a unique UUID for each message
    def test_send_generates_unique_uuid(self):
        cipher = Cipher("testkey")
        latin = Latin()
        messages = Messages(cipher, "123", latin)
        uuid1 = messages.send("Hello")
        uuid2 = messages.send("World")
        assert uuid1 != uuid2

    #  send method encrypts the message correctly using the Cipher class
    def test_send_encrypts_message_correctly(self):
        cipher = Cipher("testkey")
        latin = Latin()
        messages = Messages(cipher, "123", latin)
        encrypted_msg = messages.send("Hello")
        assert "ACCMST 123" in encrypted_msg

    #  send method handles cases where UUID generation takes multiple attempts
    def test_send_handles_multiple_uuid_attempts(self):
        cipher = Cipher("testkey")
        latin = Latin()
        messages = Messages(cipher, "123", latin)
        messages.uuid_used.append(str(uuid.uuid4()))
        new_uuid = messages.send("Hello").split()[2]
        assert new_uuid not in messages.uuid_used

    #  receive method handles messages with invalid formats gracefully
    def test_receive_handles_invalid_formats(self):
        cipher = Cipher("testkey")
        latin = Latin()
        messages = Messages(cipher, "123", latin)
        result = messages.receive("INVALID MESSAGE FORMAT")
        assert result == "INVALID MESSAGE FORMAT"

    #  receive method handles empty messages or messages shorter than expected
    def test_receive_handles_empty_or_short_messages(self):
        cipher = Cipher("testkey")
        latin = Latin()
        messages = Messages(cipher, "123", latin)
        result_empty = messages.receive("")
        result_short = messages.receive("123")
        assert result_empty == ""
        assert result_short == "123"
