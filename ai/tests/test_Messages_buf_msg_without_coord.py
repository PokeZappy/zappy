import uuid
import pytest
import re

from src.communication.messages import Messages


class TestBufMsgWithoutCoord:

    #  Generates a new UUID not in uuid_used
    def test_generates_new_uuid_not_in_uuid_used(self, mocker):
        cipher = mocker.Mock()
        cipher.encryption.return_value = "encrypted_message"
        id_number = "12345"
        language = mocker.Mock()
        messages = Messages(cipher, id_number, language)
    
        mocker.patch('uuid.uuid4', return_value=uuid.UUID('12345678123456781234567812345678'))
    
        messages.buf_msg_without_coord("Test message", 6789)
    
        assert '12345678-1234-5678-1234-567812345678' in messages.uuid_used

    #  Encrypts the message using the cipher
    def test_encrypts_message_using_cipher(self, mocker):
        cipher = mocker.Mock()
        cipher.encryption.return_value = "encrypted_message"
        id_number = "12345"
        language = mocker.Mock()
        messages = Messages(cipher, id_number, language)
    
        messages.buf_msg_without_coord("Test message", 6789)
    
        cipher.encryption.assert_called_once_with("Test message")

    #  Appends the encrypted message to self.msg with correct format when self.msg is 'Broadcast "'
    def test_appends_encrypted_message_to_self_msg_with_correct_format(self, mocker):
        cipher = mocker.Mock()
        cipher.encryption.return_value = "encrypted_message"
        id_number = "12345"
        language = mocker.Mock()
        messages = Messages(cipher, id_number, language)
    
        mocker.patch('uuid.uuid4', return_value=uuid.UUID('12345678123456781234567812345678'))
    
        messages.buf_msg_without_coord("Test message", 6789)
    
        expected_msg = 'Broadcast "ACCMST 6789 12345678-1234-5678-1234-567812345678 encrypted_message'
        assert messages.msg == expected_msg

    #  Handles case when uuid_used is initially empty
    def test_handles_case_when_uuid_used_is_initially_empty(self, mocker):
        cipher = mocker.Mock()
        cipher.encryption.return_value = "encrypted_message"
        id_number = "12345"
        language = mocker.Mock()
        messages = Messages(cipher, id_number, language)
    
        assert messages.uuid_used == [""]
    
        messages.buf_msg_without_coord("Test message", 6789)
    
        assert len(messages.uuid_used) == 2

    #  Handles case when uuid_used already contains multiple UUIDs
    def test_handles_case_when_uuid_used_contains_multiple_uuids(self, mocker):
        cipher = mocker.Mock()
        cipher.encryption.return_value = "encrypted_message"
        id_number = "12345"
        language = mocker.Mock()
        messages = Messages(cipher, id_number, language)
    
        messages.uuid_used.extend(["uuid1", "uuid2"])
    
        mocker.patch('uuid.uuid4', return_value=uuid.UUID('12345678123456781234567812345678'))
    
        messages.buf_msg_without_coord("Test message", 6789)
    
        assert '12345678-1234-5678-1234-567812345678' in messages.uuid_used

    #  Handles case when message is an empty string
    def test_handles_case_when_message_is_empty_string(self, mocker):
        cipher = mocker.Mock()
        cipher.encryption.return_value = "encrypted_message"
        id_number = "12345"
        language = mocker.Mock()
        messages = Messages(cipher, id_number, language)
    
        messages.buf_msg_without_coord("", 6789)
    
        expected_msg = 'Broadcast "ACCMST 6789  encrypted_message'

        uuid_pattern = re.compile(r'[0-9a-fA-F-]{36}')
        parts2 = uuid_pattern.split(messages.msg)
        normalized_str2 = ''.join(parts2)

        assert expected_msg == normalized_str2
