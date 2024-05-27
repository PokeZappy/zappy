import player
import socket
from src.mvt.tsp import held_krap
from src.gameplay.evolution import evolution

class role(player):

    def __int__(self, serv_info: list[int], cli_socket: socket):
        super().__int__(serv_info, cli_socket)
        self.goal = evolution()
        self.mvt = held_krap(self.limit, self.pos, self.inv, self.goal)
        self.level = 1

    def set_goal(self, level: int) -> None:
        self.goal = evolution(level)
        self.mvt.goal = self.goal

    def run(self) -> None:
        while self.level < 8:
            view = self.look_around()
            self.update_map(view)
