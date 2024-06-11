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
        # TODO: put away the 642 by a constant 2 constant and separtate the 42 from the 600
        self.serv_info = serv_info
        self.cli_socket = cli_socket
        self.debug_mode = debug_mode
        self.counter = 642
        self.role = RoleInGame.PROGENITOR
        self.machine = machine
        self.port = port
        self.name = name
    
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
            return

    # def apply_action(self, buf: str) -> None:
    #     if buf.__contains__('message'):
    #         list_message = buf.split(',')
    #         self.decode_message(list_message)
    #     elif buf.__contains__('death'):
    #         self.actions.append()

    def recv_treatment(self, buf: str) -> None:
        buf = buf[:-1]
        print(buf)
        if buf == 'ok':
            # TODO: make brodacast with cyprien

            # if self.is_broadcast(buf):
            #     self.apply_broadcast(buf)
            #     return
            # self.apply_action(buf)
            l = 1
        elif buf.isnumeric() and int(buf) > 0:
            self.real_fork()
        self.actions.pop(0)

    def make_action(self) -> None:
        """
        TODO: put away the 42 by a constant
        """
        if len(self.actions) > 10:
            return
        if self.role == RoleInGame.PROGENITOR and self.counter >= 0:
            self.counter -= 42
        self.queue.append('Fork')
        if self.role == RoleInGame.PROGENITOR and self.counter <= 0:
            self.give_birth()
        self.apply_action()
