import uuid
import pytest

from src.communication.messages import Messages


class TestBufMsgCoord:

    #  Generates a new UUID if not already used
    def test_generates_new_uuid_if_not_used(self, mocker):
        cipher = mocker.Mock()
        cipher.encryption.return_value = "encrypted_message"
        language = mocker.Mock()
        messages = Messages(cipher, "12345", language)
    
        mocker.patch('uuid.uuid4', return_value=uuid.UUID('12345678123456781234567812345678'))
    
        messages.buf_msg_coord("Test message", 6789, (10, 20))
    
        assert '12345678-1234-5678-1234-567812345678' in messages.uuid_used

    #  Appends the new UUID to the list of used UUIDs
    def test_appends_new_uuid_to_list(self, mocker):
        cipher = mocker.Mock()
        cipher.encryption.return_value = "encrypted_message"
        language = mocker.Mock()
        messages = Messages(cipher, "12345", language)
    
        mocker.patch('uuid.uuid4', return_value=uuid.UUID('12345678123456781234567812345678'))
    
        messages.buf_msg_coord("Test message", 6789, (10, 20))
    
        assert messages.uuid_used[-1] == '12345678-1234-5678-1234-567812345678'

    #  Encrypts the message correctly using the cipher
    def test_encrypts_message_correctly(self, mocker):
        cipher = mocker.Mock()
        cipher.encryption.return_value = "encrypted_message"
        language = mocker.Mock()
        messages = Messages(cipher, "12345", language)
    
        messages.buf_msg_coord("Test message", 6789, (10, 20))
    
        cipher.encryption.assert_called_once_with("Test message#10,20")

    #  Handles the case when the UUID list is initially empty
    def test_handles_empty_uuid_list(self, mocker):
        cipher = mocker.Mock()
        cipher.encryption.return_value = "encrypted_message"
        language = mocker.Mock()
        messages = Messages(cipher, "12345", language)
    
        assert messages.uuid_used == [""]
    
        messages.buf_msg_coord("Test message", 6789, (10, 20))
    
        assert len(messages.uuid_used) == 2

    #  Handles the case when the UUID list already contains multiple UUIDs
    def test_handles_multiple_uuids_in_list(self, mocker):
        cipher = mocker.Mock()
        cipher.encryption.return_value = "encrypted_message"
        language = mocker.Mock()
        messages = Messages(cipher, "12345", language)
    
        messages.uuid_used.extend(['uuid1', 'uuid2'])
    
        messages.buf_msg_coord("Test message", 6789, (10, 20))
    
        assert len(messages.uuid_used) == 4

    #  Handles messages with special characters
    def test_handles_special_characters_in_message(self, mocker):
        cipher = mocker.Mock()
        cipher.encryption.return_value = "encrypted_message"
        language = mocker.Mock()
        messages = Messages(cipher, "12345", language)
    
        special_message = "Hello, this is a test message with special characters! @#&*()"
    
        messages.buf_msg_coord(special_message, 6789, (10, 20))
    
        cipher.encryption.assert_called_once_with(special_message + "#10,20")
