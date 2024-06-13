from socket import socket

class incantator():
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
                #TODO: communication('Incantation failed')
                pass
            if self.action[0] == 'Take food':
                #TODO: communication('Need food')
                pass
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
        if self.life <= 300:
            self.queue.append('Take food')
        elif self.dir == None:
            #TODO: ask for a direction to go to
            pass
        elif self.goto != None:
            #TODO: ask for a direction to go to
            pass
        elif not self.is_in_position:
            self.queue.append('Position')
        elif self.allowed_incantation:
            self.queue.append('Incantation')
            self.allowed_incantation = False
        else:
            self.queue.append('Look')
            #TODO: commmunicate with the mastermind on the look

        self.apply_action()