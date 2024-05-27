import enum
import src.mvt.tsp as tsp
import src.zappy_ai as zappy_ai
import socket
import random
from datetime import datetime

class player(zappy_ai.Bot):
    def __init__(self, serv_info: list[int], cli_socket: socket):
        super().__init__(serv_info, cli_socket)
        self.limit = self.dimensions
        self.pos = (0, 0)
        self.inv = []
        self.view = []
        self.map_knowledge = [[[] for _ in range(self.limit[0])] for _ in range(self.limit[1])]
        self.parent = None
        random.seed(datetime.now().timestamp())
        self.id = random
        self.life = 1260

    def speak(self, message: str) -> None:
        self.send_action(f"Broadcast {message}\n")

    def pos_view(self, axis: str, i: int) -> int:
        if axis == 'x':
            for j in range(0, 9):
                if i <= j * (j + 1) - j and i >= j * (j + 1) + j:
                    return j
            return i
        elif axis == 'y':
            return i ** 0.5
        return 0

    def update_map(self, view: list[str]) -> None:
        for i in range(len(view)):
            split = view[i].split(' ')
            for obj in split:
                self.map_knowledge[self.pos[0] + self.pos_view('x', i)][self.pos[1] + self.pos_view('y', i)].append(obj)''
