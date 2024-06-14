from socket import socket

from src.player.player import Player


class Mastermind(Player):
    """
    The Mastermind class initializes
    """
    def __init__(self, serv_info: list[int], cli_socket: socket, debug_mode: bool = False):
        super().__init__(serv_info, cli_socket, debug_mode)
    
    def recv_treatment(self, buf: str) -> None:
        buf = buf[:-1]
        print(buf)
        if buf == 'ok':
            pass

    def make_action(self) -> None:
        self.apply_action()

    def broadcast_traitement(self, message: tuple | str) -> None:
        if message['msg'] == '':
            # TODO: recieve all inventory from collector
            pass
        if message['msg'] == 'opes deposita':
        #     TODO : faire lancer l'incantation si ressources ok
            pass
        if message['msg'] == 'defecit carmen':
            #TODO: problem to make the incantation
            pass
        self.global_message()
