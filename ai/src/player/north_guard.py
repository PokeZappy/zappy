import socket
from abc import ABC

from ai.src.player.player import Player
from ai.src.mvt import path
from ai.src.utils.info_look import look_resources


class NorthGuard(Player):

    def __init__(self, serv_info: list[int], cli_socket: socket, debug_mode: bool = False):
        super().__init__(serv_info, cli_socket, debug_mode)
        self.first: bool = False

    def say_the_north(self):
        """

        """
        self.message.buf_messages(message='est dominus aquilonis')
        self.queue.append('Broadcast')
        self.life -= self.ACTION

    def return_to_the_north(self):
        """

        """
    #     TODO - si poussé retourne sur sa casse Est ou Ouest avec la clear queue
        pass

    def make_action(self) -> None:
        """

        """
        if len(self.actions) >= 1:
            return self.actions
        # TODO - rajouter la grille
        if not self.first:
            self.queue.append('Forward')
            self.life -= self.ACTION
            self.first = True
        else:
            self.say_the_north()
        self.apply_action()
