from socket import socket

from ai.src.player.player import Player

class Pnj(Player):
    """
    Pnj class
    """

    def __init__(self, serv_info: list[int], cli_socket: socket, debug_mode: bool = False):
        """
        Pnj class constructor
        """
        super().__init__(serv_info, cli_socket, debug_mode)
        self.goto = None
        self.dir = None
        self.allowed_incantation_cooker = 0
        self.allowed_to_move = True
        self.first_round = True
    
    def recv_treatment(self, buf: str) -> None:
        """
        This method treats the received message.

        :param buf: str - The received message.
        :return: None
        """
        recv_type, msg = self.message.receive(buf)
        if recv_type == 'ok':
            if msg[1] == 'food':
                self.life += self.FOOD
            self.actions.pop(0)
        if recv_type == 'ko':
            self.actions.pop(0)
        elif recv_type == 'broadcast':
            self.broadcast_traitement(msg)

    def broadcast_traitement(self, message: tuple | str) -> None:
        if message['msg'] == 'felix carmen':
            self.allowed_to_move = True
            self.level += 1
            self.life -= self.INCANTATION
        if message['msg'] == 'comedent ut incant : ':
            for _ in range(message['nbr']):
                self.queue.append('Take food')
        if message['msg'] == 'movere ad : ':
            self.goto = message['info']

    def make_action(self) -> None:
        """
        This method makes the action.
        """
        if self.first_round:
            self.queue.append(('Set', 'food'))
            self.first_round = False
        if not self.allowed_to_moove:
            return
        while len(self.queue) > 0:
            self.apply_action()
        self.allowed_to_moove = False

