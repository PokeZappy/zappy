from socket import socket

from src.communication.messages import Messages


class Incantator():
    """
    Incantator class
    """

    def __init__(self, serv_info: list[int], cli_socket: socket, debug_mode: bool = False):
        """
        Incantator class constructor
        """
        super().__init__(serv_info, cli_socket, debug_mode)
        self.you_should_not_pass = True
        self.is_in_position = False
        self.goto = None

    def recv_treatment(self, buf: str) -> None:
        """
        This method treats the received message.

        :param buf: str - The received message.
        :return: None
        """
        if buf[-1] == '\n':
            buf = buf[:-1]
        if buf == 'ok':
            if self.action[0] == 'Take food':
                self.life += self.FOOD
        elif buf == 'ko':
            if self.action[0] == 'Take food':
                #TODO: communication('Need food')
                pass
        else:
            #TODO: understanding broadcast

            #TODO: set understanding in broadcast(there is food, let me pass, etc.)
            pass
        pass

    def make_action(self) -> None:
        """
        This method makes the action of the incantator.
        """
        if len(self.action) > 1:
            return
        if self.life <= 300:
            self.queue.append('Take food')
        elif self.goto != None:
            self
            #TODO: ask for a direction to go to
            pass
        elif self.is_in_position == False:
            #TODO: ask for a direction to go to
            pass
        elif self.you_should_not_pass == True:
            self.eject()
        self.apply_action()