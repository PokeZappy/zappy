from socket import socket

from ai.src.player.player import Player

class Incantator(Player):
    """
    Incantator class
    """

    def __init__(self, serv_info: list[int] | None = None, cli_socket: socket | None = None, debug_mode: bool = False):
        """
        Incantator class constructor
        """
        if serv_info is not None:
            super().__init__(serv_info, cli_socket, debug_mode)
        self.allowed_incantation_mns = 1
        self.goto = (0, 1)
        self.dir = None
        self.allowed_incantation_cooker = 0
        self.first_round = True

    def recv_treatment(self, buf: str) -> None:
        """
        This method treats the received message.

        :param buf: str - The received message.
        :return: None
        """
        if len(self.actions) == 0:
            recv_list = self.message.receive(buf)
        else:
            recv_list = self.message.receive(buf, self.actions[0])
        for recv_type, msgs in recv_list:
            if recv_type == 'ok':
                if msgs == 'Incantation':
                    self.level += 1
                if msgs[0] == 'Take' and msgs[1] == 'food':
                    self.life += self.FOOD
            elif recv_type == 'ko':
                if msgs == 'Incantation':
                    self.allowed_incantation_mns -= 1
                    self.message.buf_messages('defecit carmen')
                    self.queue.append('Broadcast')
                if msgs[0] == 'Take' and msgs[1] == 'food':
                    self.message.buf_messages('cibo opus est')
                    self.waiting_food = True
                    self.queue.append('Broadcast')
            elif recv_type == 'broadcast':
                if msgs[0] == 'ko':
                    continue
                for msg in msgs:
                    self.broadcast_traitement(msg)
                continue
            self.actions.pop(0)



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
        if len(self.queue) > 0:
            self.apply_action()
        if len(self.actions) > 1:
            return
        if self.life <= 400:
            self.queue.append('Take food')
        if self.dir == None:
            #TODO: find the direction to go north the incantation (asign Cyprien)
            pass
        if self.goto != None:
            #TODO: (0, 1) -> first incantation when level 2 -> incantation in (0, 0) (asign Cyprien)
            pass
        if self.allowed_incantation_mns > self.level:
            self.queue.append('Incantation')
        else:
            self.queue.append('Look')
            #TODO: commmunicate with the mastermind on the look
        # self.apply_action()
