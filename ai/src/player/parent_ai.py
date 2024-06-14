from os import fork
from src.player.progenitor import Progenitor
from src.player.player import Player
from src.zappy_ai import connection
from socket import socket
from src.gameplay.enum_gameplay import RoleInGame

class ParentAI(Player):
    def __init__(self, serv_info: list[int], cli_socket: socket, debug_mode: bool = False,
                 machine: str = None, port: str = None, name: str = None):
        super().__init__(serv_info, cli_socket, debug_mode)
        self.serv_info = serv_info
        self.cli_socket = cli_socket
        self.debug_mode = debug_mode
        self.counter = self.INCUBATION_TIME + self.FORK_ACTION
        self.gave_birth = 0
        self.role = RoleInGame.MASTERMIND
        self.machine = machine
        self.port = port
        self.name = name
        self.first_round = [True, True]
    
    def fork(self, role: RoleInGame) -> None:
        match role:
            case RoleInGame.PROGENITOR:
                serv_info, cli_socket = connection(self.port, self.name, self.machine)
                bot = Progenitor(serv_info, cli_socket, self.debug_mode)
                bot.run()

    def give_birth(self) -> None:
        self.queue.append('Slots')

    def choose_role(self) -> RoleInGame:
        if self.role == RoleInGame.PROGENITOR:
            return RoleInGame.PROGENITOR

    def real_fork(self) -> None:
        role = self.choose_role()
        pid = fork()
        if pid == -1:
            return
        elif pid == 0:
            self.fork(role)
        else:
            self.gave_birth += 1
            return

    # def apply_action(self, buf: str) -> None:
    #     if buf.__contains__('message'):
    #         list_message = buf.split(',')
    #         self.decode_message(list_message)
    #     elif buf.__contains__('death'):
    #         self.actions.append()

    def real_fork_addaptativ(self) -> None:
        #TODO: implement the real_fork_addaptativ with cyprien
        #TODO: see how we handle the strategy with him
        pass

    def mastermind_treatment(self, buf) -> bool:
        """"
        mastermind treatment informations

        :return false: if he received a broadcast
        :return true: else
        """
        if buf == 'ok':
            self.update_ok()
        elif isinstance(buf, str) and buf.isnumeric() and int(buf) > 0:
            counter = int(buf)
            for _ in range(counter, 0, -1):
                self.real_fork()
        else:
            self.get_broadcast(buf)
            # TODO: communication broadcast
            return False

    def recv_treatment(self, buf: str) -> None:
        buf = buf[:-1]
        print(buf)
        if self.first_round[1] and isinstance(buf, str) and buf.isnumeric():
            for _ in range(int(buf), 0, -1):
                self.real_fork_addaptativ()
            self.first_round[1] = False
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
            else:
                #TODO: communication broadcast
                return
        elif RoleInGame.MASTERMIND:
            if not self.mastermind_treatment(buf):
                return
        self.actions.pop(0)

    def action_as_progenitor(self) -> None:
        """
        This is being used when parent_ai is a progenitor
        """
        if self.counter >= 0:
            self.counter -= self.FORK_ACTION
        self.queue.append('Fork')
        if self.counter <= 0:
            self.give_birth()
        if self.gave_birth == 2:
            self.role = RoleInGame.MASTERMIND


    def communicate_orders(self) -> None:
        """
        This method communicates the orders to the mastermind.
        """
        #TODO: implement the communication between the mastermind and the putas

        pass

    def action_as_mastermind(self) -> None:
        """
        This is being used when parent_ai is a mastermind
        """
        if len(self.queue) > 1:
            return
        self.queue.append('Slots')
        if self.life <= self.HUNGRY and self.nbr_food > 0:
            self.queue.append('Take food')
        else:
            self.communicate_orders()

    def make_action(self) -> None:
        """
        This method makes the action of the player.
        """
        if self.first_round[0]:
            self.queue.append('Slots')
            self.first_round[0] = False
        if self.first_round[1]:
            return
        if self.role == RoleInGame.PROGENITOR:
            self.action_as_progenitor()
        elif self.role == RoleInGame.MASTERMIND:
            self.action_as_mastermind()
        self.apply_action()

    def get_broadcast(self, broadcast_recv: str):
        print(broadcast_recv)
