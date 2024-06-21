from socket import socket
import re

from ai.src.player.player import Player

class Pnj(Player):
    """
    Pnj class
    """

    def __init__(self, serv_info: list[int] | None = None, cli_socket: socket | None = None, debug_mode: bool = False):
        """
        Pnj class constructor
        """
        if serv_info is not None:
            super().__init__(serv_info, cli_socket, debug_mode)
        self.goto = None
        self.dir = None
        self.first_round = True
    
    def recv_treatment(self, buf: str) -> None:
        """
        This method treats the received message.

        :param buf: str - The received message.
        :return: None
        """
        super().recv_treatment(buf)
        match = re.match(r'Current level: (\d+)\n', buf)
        if match:
            if int(match.group(1)) == 2:
                print('I am level 2, here')
                self.queue.append('Right')
                self.queue.append('Right')
                self.queue.append('Forward')
            self.queue.append(('Take', 'food'))
            self.queue.append(('Take', 'food'))
            self.queue.append(('Take', 'food'))
            if int(match.group(1)) == 2:
                self.message.buf_messages('motus sum')
                self.queue.append('Broadcast')

        

    def broadcast_traitement(self, message: tuple | str) -> None:
        if message['msg'] == 'movere ad : ':
            self.goto = message['info']
        if message['msg'] == 'est dominus aquilonis':
            if self.path.facing is None:
                self.get_north(message['direction'])
                if self.path.facing == 0:
                    self.queue.append('Left')
                    self.queue.append('Forward')
                elif self.path.facing == 3:
                    self.queue.append('Forward')
                elif self.path.facing == 2:
                    self.queue.append('Right')
                    self.queue.append('Forward')
                else:
                    self.queue.append('Right')
                    self.queue.append('Right')
                    self.queue.append('Forward')
                self.message.buf_messages('motus sum')
                self.queue.append('Broadcast')

    def make_action(self) -> None:
        """
        This method makes the action.
        """
        if self.first_round:
            self.queue.append(('Set', 'food'))
            self.first_round = False
        if len(self.queue) > 0 and len(self.actions) < 1:
            self.apply_action()
        if len(self.actions) > 0:
            return
        

