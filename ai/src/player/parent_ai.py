from os import fork

from ai.src.player.progenitor import Progenitor
from ai.src.player.collector import Collector
from ai.src.player.incantator import Incantator
from ai.src.player.player import Player
from ai.src.player.pnj import Pnj
from ai.src.player.first_born import First_born
from ai.src.player.north_guard import NorthGuard
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
        RoleInGame.NORTH_GUARD: NorthGuard,
        RoleInGame.PNJ: Pnj,
        RoleInGame.FIRST_BORN: First_born
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
        self.coll_ressources = {}
        self.level_incant = 1
        self.global_ressources = self.based_ressources
        self.new_focus = False
        self.ressources_focus = {}
        self.allow_incantation = False
    
    def fork(self, role: RoleInGame) -> None:
        serv_info, cli_socket = connection(self.port, self.name, self.machine)
        role = self.BIND[role](serv_info, cli_socket, self.debug_mode).run()
        if role is not None:
            print(type(role))
            role = self.BIND[role](serv_info, cli_socket, self.debug_mode).run()
        exit(0)

    def real_fork(self) -> None:
        pid = fork()
        if pid == 0:
            if self.first_round[1]:
                self.fork(RoleInGame.FIRST_BORN)
            else:
                self.fork(self.DEFAULT_ROLE if len(self.give_role) == 0 else self.give_role[0])

    # def apply_action(self, buf: str) -> None:
    #     if buf.__contains__('message'):
    #         list_message = buf.split(',')
    #         self.decode_message(list_message)
    #     elif buf.__contains__('death'):
    #         self.actions.append()
    # [m_info, m_nbr] for m_info, m_nbr in zip(message['info'], message['nbr'])

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
        if message['msg'] == 'opes in meo inventario sunt : ':
            if message['id'] not in self.coll_ressources.keys():
                self.coll_ressources[message['id']] = self.based_ressources
            for keys, nbrs in zip(message['info'], message['nbr']):
                self.coll_ressources[message['id']][keys] = nbrs
                self.global_ressources[keys] += nbrs

        if message['msg'] == 'opes deposita':
            for keys, nbrs in zip(message['info'], message['nbr']):
                self.global_ressources[keys] -= nbrs
                self.ressources_focus[keys]-= nbrs
            if any(item <= 0 for item in self.ressources_focus.values()):
                self.new_focus = True
                self.message.buf_messages('facultates positas carmina')
        if message['msg'] == 'defecit carmen':
            #TODO: problem to make the incantation
            pass
        if message['msg'] == 'felix carmen':
            self.level_incant += 1

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

        if self.allow_incantation:
            self.message.buf_messages('facultates positas carmina')
            self.queue.append('Broadcast')
            self.allow_incantation = False
            return True
        if self.level_to_give == self.level_incant and self.new_focus:
            self.message.buf_messages('quid habes ut nobis offerat')
            self.queue.append('Broadcast')
            self.level_to_give += 1
            self.new_focus = False
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
        print('action as mastermind')
        if self.life <= 300:
            self.queue.append(('Take', 'food'))
        elif not self.communicate_orders():
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
