import src.player as ply
from src.zappy_ai import Bot
from socket import socket
from src.gameplay.enum_gameplay import RoleInGame

class ParentAI(ply.PLayer):
    def __init__(self, serv_info: list[int], cli_socket: socket, debug_mode: bool = False):
        super.__init__(serv_info, cli_socket, debug_mode)
        # TODO: put away the 642 by a constant 2 constant and separtate the 42 from the 600
        self.counter = 642
        self.role = RoleInGame.PROGENITOR
    
    def fork(self, role: RoleInGame, serv_info: list[int], cli_socket: socket, debug_mode: bool) -> ply.Player:
        match role:
            case RoleInGame.PROGENITOR:
              return ply.Progenitor(serv_info, cli_socket, debug_mode)

    def give_birth(self):
        self.nbr_of_slot()
        self.actions.append('Slots\n')
    
    def apply_action(self, buf: str) -> None:
        if buf.__contains__('message'):
            list_message = buf.split(',')
            self.decode_message(list_message)
        elif buf.__contains__('death'):
            self.actions.append()

    def recv_treatment(self, buf: str) -> None:
        if buf != 'ok\n':
            if self.is_broadcast(buf):
                self.apply_broadcast(buf)
                return
            self.apply_action(buf)
        self.actions.pop(0)

    def make_action(self):
        """
        TODO: put away the 42 by a constant
        """
        if len(self.actions) > 10:
            return
        if self.role == RoleInGame.PROGENITOR and self.counter >= 0:
            self.counter -= 42
        if self.role == RoleInGame.PROGENITOR and self.counter <= 0:
            self.give_birth()
