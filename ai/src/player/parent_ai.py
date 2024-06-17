from os import fork

from ai.src.player.progenitor import Progenitor
from ai.src.player.collector import Collector
from ai.src.player.incantator import Incantator
from ai.src.player.player import Player
from ai.src.zappy_ai import connection
from socket import socket
from ai.src.gameplay.enum_gameplay import RoleInGame

class ParentAI(Player):

    ROLE = [
            RoleInGame.PROGENITOR,
            RoleInGame.PROGENITOR,
            RoleInGame.PROGENITOR,
            RoleInGame.INCANTATOR,
            RoleInGame.PNJ,
            RoleInGame.PNJ,
            RoleInGame.PNJ,
            RoleInGame.PNJ,
            RoleInGame.PNJ,
            RoleInGame.COLLECTOR,
            RoleInGame.COLLECTOR,
            RoleInGame.COLLECTOR,
            RoleInGame.COLLECTOR,
            RoleInGame.PUSHER,
            RoleInGame.PUSHER,
            RoleInGame.PUSHER,
            RoleInGame.PUSHER,
            RoleInGame.COOCKER,
            RoleInGame.COLLECTOR,
            RoleInGame.COLLECTOR,
            RoleInGame.COLLECTOR,
            RoleInGame.COLLECTOR,
            ]
    DEFAULT_ROLE = RoleInGame.COLLECTOR

    BIND = {
        RoleInGame.PROGENITOR: Progenitor,
        RoleInGame.COLLECTOR: Collector,
        RoleInGame.INCANTATOR: Incantator
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
        

    def mastermind_treatment(self, buf) -> None:
        """"
        mastermind treatment informations

        :return false: if he received a broadcast
        :return true: else
        """
        recv_type, msg = self.message.receive(buf, self.actions[0])
        if recv_type == 'ok':
            if msg == 'Broadcast':
                self.broadcast_traitement(msg)
            if msg[1] == 'food':
                self.life += self.FOOD
        elif isinstance(buf, str) and buf.isnumeric() and int(buf) > 0:
            counter = int(buf)
            for _ in range(counter, 0, -1):
                self.real_fork()
                self.give_role.pop(0)
        elif recv_type == 'broadcast':
            self.broadcast_traitement(msg)
            return False
        return True

        def broadcast_traitement(self, message: tuple | str) -> None:
            if message['msg'] == '':
                # TODO: recieve all inventory from collector
                pass
            if message['msg'] == 'opes deposita':
            #     TODO : faire lancer l'incantation si ressources ok
                pass
            if message['msg'] == 'defecit carmen':
                #TODO: problem to make the incantation
                pass
            self.global_message()


    def recv_treatment(self, buf: str) -> None:
        buf = buf[:-1]
        print(buf)
        
        if self.first_round[1] and isinstance(buf, str) and buf.isnumeric():
            for _ in range(0, int(buf)):
                self.real_fork()
        if self.first_round[1]:
            self.first_round[1] = False
            self.give_role = self.ROLE
        if self.role == RoleInGame.PROGENITOR:
            if buf == 'ok':
                # TODO: make brodacast with cyprien
                # if self.is_broadcast(buf):
                #     self.apply_broadcast(buf)
                #     return
                # self.apply_action(buf)
                l = 1
            elif isinstance(buf, str) and buf.isnumeric() and int(buf) > 0:
                counter = int(buf)
                for _ in range(counter, 0, -1):
                    self.real_fork()
                    self.give_role.pop(0)

            else:
                #TODO: communication broadcast
                return
        elif RoleInGame.MASTERMIND:
            self.mastermind_treatment(buf)
        self.actions.pop(0)

    def action_as_progenitor(self) -> None:
        """
        This is being used when parent_ai is a progenitor
        """
        self.queue.append('Fork')
        if self.counter > 0:
            self.counter -= self.FORK_ACTION
        if self.counter <= 0:
            self.queue.append('Slots')
        if RoleInGame.PROGENITOR not in self.give_role:
            self.role = RoleInGame.MASTERMIND

    def communicate_orders(self) -> None:
        """
        This method communicates the orders to the mastermind.
        """
        #TODO: implement the communication between the mastermind and the putas

        if RoleInGame.PNJ not in self.give_role and not self.can_incant:
            self.broadcast('facultates positas carmina')
            self.can_incant = True

    def action_as_mastermind(self) -> None:
        """
        This is being used when parent_ai is a mastermind
        """
        if len(self.queue) > 1:
            return
        if len(self.queue) > 0:
            self.apply_action()
            return
        self.queue.append('Slots')
        if self.life <= 300:
            self.queue.append(('Take', 'food'))
        else:
            self.communicate_orders()

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
        elif self.role == RoleInGame.MASTERMIND:
            self.action_as_mastermind()
        self.apply_action()

    def get_broadcast(self, broadcast_recv: str):
        print(broadcast_recv)
