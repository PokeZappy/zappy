from socket import socket

from ai.src.player.player import Player

class Incantator(Player):
    """
    Incantator class
    """

    def __init__(self, serv_info: list[int], cli_socket: socket, debug_mode: bool = False):
        """
        Incantator class constructor
        """
        super().__init__(serv_info, cli_socket, debug_mode)
        self.allowed_incantation_mns = 1
        self.goto = None
        self.dir = None
        self.allowed_incantation_cooker = 0
        self.first_round = True

    def recv_treatment(self, buf: str) -> None:
        """
        This method treats the received message.

        :param buf: str - The received message.
        :return: None
        """
        recv_type, msg = self.message.receive(buf, self.actions[0])
        if recv_type == 'ok':
            if msg == 'Incantation':
                self.level += 1
            if msg[1] == 'food':
                self.life += self.FOOD
            self.actions.pop(0)
        elif recv_type == 'ko':
            if msg == 'Incantation':
                self.allowed_incantation_mns -= 1
                self.message.buf_messages('defecit carmen')
                self.queue.append('Broadcast')
            if msg == 'Take food':
                self.message.buf_messages('cibo opus est')
                self.waiting_food = True
                self.queue.append('Broadcast')
        elif recv_type == 'broadcast':
            self.broadcast_traitement(msg)


        def broadcast_traitement(self, message: tuple | str) -> None:
            if message['msg'] == 'facultates positas carmina':
                self.allowed_incantation_mns += 1
            if message['msg'] == 'comedent ut incant : ':
                self.wating_food = False
                self.food_can_be_taken = True
            if message['msg'] == 'comedent ut incant : ':
                if message['info'] == 'cibus':
                    self.allowed_incantation_cooker = message['nbr']
            if message['msg'] == 'movere ad : ':
                self.goto = message['info']
            # TODO: see utility of self.global_message()


    def make_action(self) -> None:
        """
        This method makes the action of the incantator.
        """
        if self.first_round:
            self.queue.append(('Set', 'food'))
            self.first_round = False
        if len(self.action) > 1:
            return
        if len(self.queue) > 0:
            self.apply_action()
            return
        if self.life <= 400:
            self.queue.append('Take food')
        elif self.goto != None:
            #TODO: ask for a direction to go to cyprien
            pass
        elif self.allowed_incantation_mns > self.level:
            self.queue.append('Incantation')
        else:
            self.queue.append('Look')
            #TODO: commmunicate with the mastermind on the look
        self.apply_action()


    def broadcast_traitement(self, message: tuple | str) -> None:
        if message['msg'] == 'facultates positas carmina':
            self.allowed_incantation += 1
        self.global_message()
