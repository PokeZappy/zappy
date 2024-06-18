from os import fork

from ai.src.player.progenitor import Progenitor
from ai.src.player.collector import Collector
from ai.src.player.incantator import Incantator
from ai.src.player.player import Player
from ai.src.player.pnj import Pnj
from ai.src.zappy_ai import connection
from socket import socket
from ai.src.gameplay.enum_gameplay import RoleInGame

class ParentAI(Player):

    ROLE = [
            # RoleInGame.PROGENITOR,
            # RoleInGame.PROGENITOR,
            RoleInGame.PROGENITOR,
            RoleInGame.INCANTATOR,
            RoleInGame.PNJ,
            RoleInGame.PNJ,
            RoleInGame.PNJ,
            RoleInGame.PNJ,
            RoleInGame.PNJ,
            # RoleInGame.COLLECTOR,
            # RoleInGame.COLLECTOR,
            # RoleInGame.COLLECTOR,
            # RoleInGame.COLLECTOR,
            # RoleInGame.PUSHER,
            # RoleInGame.PUSHER,
            # RoleInGame.PUSHER,
            # RoleInGame.PUSHER,
            # RoleInGame.COOCKER,
            # RoleInGame.COLLECTOR,
            # RoleInGame.COLLECTOR,
            # RoleInGame.COLLECTOR,
            # RoleInGame.COLLECTOR,
            ]
    DEFAULT_ROLE = RoleInGame.PNJ

    BIND = {
        RoleInGame.PROGENITOR: Progenitor,
        RoleInGame.COLLECTOR: Collector,
        RoleInGame.INCANTATOR: Incantator,
        RoleInGame.PNJ: Pnj
    }

    def __init__(self, serv_info: list[int], cli_socket: socket, debug_mode: bool = False,
                 machine: str = None, port: str = None, name: str = None):
        super().__init__(serv_info, cli_socket, debug_mode)
        self.serv_info = serv_info
        self.cli_socket = cli_socket
        self.debug_mode = debug_mode
        self.counter = self.INCUBATION_TIME + self.FORK_ACTION
        self.gave_birth = 0
        self.role = RoleInGame.PROGENITOR
        self.machine = machine
        self.port = port
        self.name = name
        self.first_round = [True, True]
        self.index = 0
        self.give_role = []
        self.can_incant = False
        self.level_to_give = 1
        self.fork_gave = 0
    
    def fork(self, role: RoleInGame) -> None:
        serv_info, cli_socket = connection(self.port, self.name, self.machine)
        bot = self.BIND[role](serv_info, cli_socket, self.debug_mode)
        bot.run()

    def real_fork(self) -> None:
        pid = fork()
        if pid == 0:
            self.fork(self.DEFAULT_ROLE if len(self.give_role) == 0 else self.give_role[0])

    # def apply_action(self, buf: str) -> None:
    #     if buf.__contains__('message'):
    #         list_message = buf.split(',')
    #         self.decode_message(list_message)
    #     elif buf.__contains__('death'):
    #         self.actions.append()

    def real_fork_addaptativ(self) -> None:
        #TODO: implement the real_fork_addaptativ with cyprien
        #TODO: see how we handle the strategy with him
        if len(self.give_role) == 0:
            return self.DEFAULT_ROLE
        

    def mastermind_treatment(self, buf) -> bool:
        """"
        mastermind treatment informations

        :return false: if he received a broadcast
        :return true: else
        """
        if len(self.actions) == 0:
            recv_list = self.message.receive(buf)
        else:
            recv_list = self.message.receive(buf, self.actions[0])
        for recv_type, msgs in recv_list:
            if recv_type == 'slots':
                for _ in range(msgs):
                    self.real_fork()
                    if len(self.give_role) > 0:
                        self.give_role.pop(0)
            elif recv_type == 'ok':
                if msgs[0] == 'Take' and msgs[1] == 'food':
                    self.life += self.FOOD
            elif recv_type == 'broadcast':
                if msgs[0] == 'ko':
                    continue
                for msg in msgs:
                    self.broadcast_traitement(msg)
                continue
            self.actions.pop(0)

    def broadcast_traitement(self, message: tuple | str) -> None:
        if message['msg'] == 'tamer':
            # TODO: recieve all inventory from collector
            pass
        if message['msg'] == 'opes deposita':
        #     TODO : faire lancer l'incantation si ressources ok
            pass
        if message['msg'] == 'defecit carmen':
            #TODO: problem to make the incantation
            pass
        self.global_message()

    def progenitor_treatment(self, buf: str) -> None:
        if len(self.actions) == 0:
            recv_list = self.message.receive(buf)
        else:
            recv_list = self.message.receive(buf, self.actions[0])
        for recv_type, msgs in recv_list:
            if recv_type == 'ok' or recv_type == 'ko':
                # TODO: make brodacast with cyprien
                # if self.is_broadcast(buf):
                #     self.apply_broadcast(buf)
                #     return
                # self.apply_action(buf)
                l = 1
            else:
                #TODO: communication broadcast
                continue
            self.actions.pop(0)


    def recv_treatment(self, buf: str) -> None:
        buf = buf[:-1]
        print(buf)
        print(self.queue)
        print(self.actions)
        if self.first_round[1] and isinstance(buf, str) and buf.isnumeric():
            for _ in range(0, int(buf)):
                self.real_fork()
        if self.first_round[1]:
            self.first_round[1] = False
            self.give_role = self.ROLE
        elif self.role == RoleInGame.PROGENITOR:
            if not self.progenitor_treatment(buf):
                return
        elif self.role == RoleInGame.MASTERMIND:
            if not self.mastermind_treatment(buf):
                return
        self.actions.pop(0)

    def action_as_progenitor(self) -> None:
        """
        This is being used when parent_ai is a progenitor
        """
        self.queue.append('Fork')
        if self.counter > 0:
            self.counter -= self.FORK_ACTION
        print (self.counter)
        if self.counter <= 0:
            self.queue.append('Slots')
            self.fork_gave += 1
        if self.fork_gave == 1:
            self.role = RoleInGame.MASTERMIND

    def communicate_orders(self) -> bool:
        """
        This method communicates the orders to the mastermind.
        """
        #TODO: implement the communication between the mastermind and the putas

        if RoleInGame.PNJ not in self.give_role and self.level_to_give <= 1:
            self.message.buf_messages('facultates positas carmina')
            self.broadcast()
            self.can_incant = True
            self.level_to_give += 1
            return True
        return False

    def action_as_mastermind(self) -> None:
        """
        This is being used when parent_ai is a mastermind
        """
        if len(self.queue) > 0:
            self.apply_action()
        if len(self.actions) > 0:
            return
        print('mastermind')
        if self.life <= 300:
            self.queue.append(('Take', 'food'))
        if not self.communicate_orders():
            print('communicate orders')
            self.queue.append('Look')
        self.queue.append('Slots')


    def make_action(self) -> None:
        """
        This method makes the action of the player.
        """
        if self.first_round[0]:
            self.queue.append('Slots')
            self.first_round[0] = False
            self.apply_action()
        if self.first_round[1]:
            return
        if self.role == RoleInGame.PROGENITOR:
            self.action_as_progenitor()
            self.apply_action()
        elif self.role == RoleInGame.MASTERMIND:
            self.action_as_mastermind()

    def get_broadcast(self, broadcast_recv: str):
        print(broadcast_recv)
