from src.player.player import Player
import socket
from src.mvt.path import Path
from src.mvt.tsp import held_krap
from src.gameplay.evolution import evolution
from src.gameplay.enum_gameplay import Ressources as res
from src.gameplay.utils import is_all_val0

class Role(Player):

    def __int__(self, serv_info: list[int], cli_socket: socket):
        super().__int__(serv_info, cli_socket)
        self.goal = evolution()
        self.mvt = held_krap(self.limit, self.pos, self.inv, self.goal)
        self.vitals = {"food": 1}

    def set_goal(self) -> None:
        self.goal = evolution(self.level)
        self.mvt.goal = self.goal

    def update_goals(self) -> None:
        if self.life < 300:
            for i in range(len(self.map_knowledge[self.pos[1]][self.pos[0]])):
                if i == res.FOOD:
                    self.take_obj()
                    return
            self.mvt.goal = self.vitals
            mvt = self.mvt.algo()
            self.move(mvt, self.dir)
            self.take_obj()
            self.mvt.goal = self.goal
        if is_all_val0(self.goal) and self.pos == (0, 0):
            result = self.incantation()
            if result:
                self.level += 1
                self.set_goal()

    def run(self) -> None:
        while self.level < 8:
            view = self.look_around()
            self.update_map(view, self.dir)
            if not is_all_val0(self.goal, not_contains=["PLAYER"]):
                move = self.mvt.algo()
                self.move(move, self.dir)
                for i in self.goal.keys():
                    for j in self.map_knowledge[self.pos[1]][self.pos[0]].keys():
                        if i == j:
                            self.take_obj()
                            self.goal[i] -= 1
            elif is_all_val0(self.goal):
                self.create_egg()
            else:
                Path(self.limit, self.pos, (0, 0)).opti_path()
            self.update_goals()
