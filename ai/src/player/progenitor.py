from src.player.player import Player
import socket

class Progenitor(Player):

    def __init__(self, serv_info: list[int], cli_socket: socket, debug_mode: bool = False):
        super().__init__(serv_info, cli_socket, debug_mode)
        self.need_eat = 0
        self.pos = (0, 0)
        self.the_place_to_be = (0, 0)
        self.nbr_of_child_to_create = -1

    def directives(self, buf: str) -> None:
        #TODO: implement the directives recieved with the broadcast
        pass

    def recv_treatment(self, buf: str) -> None:
        """
        This method treats the received message.

        :param buf: str - The received message.
        :return: None
        """
        if buf != 'ok\n':
            self.directives(buf)
        self.actions.pop(0)
    
    def make_action(self) -> None:
        if self.the_place_to_be != self.pos:
            self.move_to(self.the_place_to_be)
        elif self.need_eat > 0:
            self.need_eat -= 1
            self.queue = [ele for ele in self.queue if ele != 'Fork']
            self.queue.append(['Take', 'food'])
        else:
            if self.nbr_of_child_to_create > 0 or self.nbr_of_child_to_create == -1:
                self.queue.append('Fork')
                if self.nbr_of_child_to_create != -1:
                    self.nbr_of_child_to_create -= 1
        if len(self.queue) > 0:
            self.apply_action()
    
