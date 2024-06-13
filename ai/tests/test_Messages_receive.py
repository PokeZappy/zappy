import pytest

from src.communication.latin import Latin
from src.communication.cipher import Cipher
from src.communication.messages import Messages


class TestReceive:

    #  returns 'ok\n' when message is 'ok\n'
    def test_returns_ok_when_message_is_ok(self, mocker):
        cipher = Cipher("testkey")
        latin = Latin()
        messages = Messages(cipher, "123", latin)
        result = messages.receive('ok\n')
        assert result == 'ok\n'

    #  returns 'ko\n' when message is 'ko\n'
    def test_returns_ko_when_message_is_ko(self, mocker):
        cipher = Cipher("testkey")
        latin = Latin()
        messages = Messages(cipher, "123", latin)
        result = messages.receive('ko\n')
        assert result == 'ko\n'

    #  handles messages with invalid formats gracefully
    def test_handles_invalid_formats_gracefully(self, mocker):
        cipher = Cipher("testkey")
        latin = Latin()
        messages = Messages(cipher, "123", latin)
        result = messages.receive('INVALID MESSAGE FORMAT')
        assert result == []
