from socket import socket
from re import match

from ai.src.player.player import Player


class Inquisitor(Player):

    def __init__(self, serv_info: list[int] | None = None, cli_socket: socket | None = None, debug_mode: bool = False):
        if serv_info is not None:
            super().__init__(serv_info, cli_socket, debug_mode)
        self.start = True
        self.i_will_push_him = False
    
    def to_go_to_the_ennemy(self, nbr :int) -> None:
        match nbr:
            case 0:
                self.queue.append('Eject')
            case 1:
                self.queue.append('Forward')
                self.queue.append('Forward')
            case 2:
                self.queue.append('Forward')
                self.queue.append('Forward')
                self.queue.append('Right')
                self.queue.append('Forward')
            case 3:
                self.queue.append('Right')
                self.queue.append('Forward')
                self.queue.append('Forward')
            case 4:
                self.queue.append('Right')
                self.queue.append('Forward')
                self.queue.append('Forward')
                self.queue.append('Right')
                self.queue.append('Forward')
            case 5:
                self.queue.append('Right')
                self.queue.append('Right')
                self.queue.append('Forward')
                self.queue.append('Forward')
            case 6:
                self.queue.append('Left')
                self.queue.append('Forward')
                self.queue.append('Forward')
                self.queue.append('Left')
                self.queue.append('Forward')
            case 7:
                self.queue.append('Left')
                self.queue.append('Forward')
                self.queue.append('Forward')
            case 8:
                self.queue.append('Forward')
                self.queue.append('Forward')
                self.queue.append('Left')
                self.queue.append('Forward')

    def recv_treatment(self, buf) -> None:
        if len(self.actions) == 0:
            recv_list = self.message.receive(buf)
        else:
            recv_list = self.message.receive(buf, self.actions[0])
        for recv_type, msgs in recv_list:
            if recv_type == 'broadcast':
                if msgs == 'ko':
                    pass
            if recv_type == 'eject':
                self.i_will_push_him = True
    def broadcast_treatment(self) -> None:
        pass

    def make_action(self) -> None:
        if len(self.queue) > 0:
            self.apply_action()
        if len(self.actions) > 2:
            return
        if self.start:
            self.queue.append('Look')
    
    def broadcast_traitement(self, message: tuple | str) -> None:
        self.global_message(message)
