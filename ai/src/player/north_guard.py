from socket import socket
from abc import ABC

from ai.src.player.player import Player
from ai.src.mvt import path


class NorthGuard(Player):

    def __init__(self, serv_info: list[int] | None = None, cli_socket: socket | None = None, debug_mode: bool = False, first: bool = False):
        if serv_info is not None:
            super().__init__(serv_info, cli_socket, debug_mode)
        self.first: bool = first
        self.take_the_pole()
        self.said = False

    def say_the_north(self):
        """

        """
        self.message.buf_messages(message='est dominus aquilonis')
        self.queue.append('Broadcast')
        self.life -= self.ACTION

    def take_the_pole(self) -> None:
        if not self.first:
            # TODO - ajuster les conditions
            self.turn_to_the_north()
        self.eject_security = False
        self.queue.append('Forward')
        self.queue.append('Forward')
        self.life -= self.ACTION * 2
        self.first = True
        self.eject_security = True

    def broadcast_traitement(self, message: tuple | str) -> None:
        if message['msg'] == 'est dominus aquilonis' and self.first is False:
            if self.path.facing is None:
                self.path.get_north(message['direction'])
                self.turn_to_the_north()
        self.global_message(message)

    def make_action(self) -> None:
        """

        """
        if len(self.actions) >= 1 or len(self.queue) > 6:
            return
        if self.life <= 142 and self.said is False:
            self.message.buf_messages(message='Ego plus viribus')
            self.queue.append('Broadcast')
            self.said = True
        self.say_the_north()
        self.apply_action()
