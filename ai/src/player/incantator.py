from socket import socket

from src.player.player import Player

class Incantator(Player):
    """
    Incantator class
    """

    def __init__(self, serv_info: list[int], cli_socket: socket, debug_mode: bool = False):
        """
        Incantator class constructor
        """
        super().__init__(serv_info, cli_socket, debug_mode)
        self.allowed_incantation = False
        self.is_in_position = False
        self.goto = None
        self.dir = None

    def recv_treatment(self, buf: str) -> None:
        """
        This method treats the received message.

        :param buf: str - The received message.
        :return: None
        """
        if buf[-1] == '\n':
            buf = buf[:-1]
        if buf == 'ok':
            if self.action[0] == 'Incantation':
                self.level += 1
            if self.action[0] == 'Take food':
                self.life += self.FOOD
        elif buf == 'ko':
            if self.action[0] == 'Incantation':
                self.message.buf_messages('nobilis incantatio')
            if self.action[0] == 'Take food':
                self.message.buf_messages('cibo opus est')
                self.queue.append('Broadcast')
        else:
            #TODO: communication(Look)

            #TODO: understanding broadcast

            #TODO: set understanding in broadcast(there is food, you can incantate, etc.)
            pass
        pass

    def make_action(self) -> None:
        """
        This method makes the action of the incantator.
        """
        if len(self.action) > 1:
            return
        if self.life <= 500:
            self.queue.append('Take food')
        elif self.goto != None:
            #TODO: ask for a direction to go to
            pass
        elif self.allowed_incantation:
            self.queue.append('Incantation')
            self.allowed_incantation = False
        else:
            self.queue.append('Look')
            #TODO: commmunicate with the mastermind on the look


    def broadcast_traitement(self, message: tuple | str) -> None:
        # if message['msg'] == 'dominus servivit : ':
        #     # TODO: prendre X bouffes sur sa case pour se mettre à 4 bouffe
        #     pass
        if message['msg'] == 'facultates positas carmina':
        #     TODO - lancer l'incantation
            pass
        self.global_message()
