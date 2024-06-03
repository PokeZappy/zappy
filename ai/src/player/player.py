import src.mvt.tsp as tsp
import src.zappy_ai as zappy_ai
import socket
import random
from src.gameplay.enum_gameplay import Directions as dir
from datetime import datetime
from src.mvt.path import Path
from src.gameplay.enum_gameplay import Ressources as res


class Player(zappy_ai.Bot):
    def __init__(self, serv_info: list[int], cli_socket: socket, debug_mode: bool = False):
        """
        This class is the player class.
        
        :param serv_info: list[int] - Information about the server.
        :param cli_socket: socket - The client socket for communication.
        :param debug_mode: bool - The debug mode.
        """
        super().__init__(serv_info, cli_socket, debug_mode)
        self.limit = self.dimensions
        self.pos = (0, 0)
        self.goal = {}
        self.inv = {}
        self.view = []
        self.map_knowledge = [[{} for _ in range(self.limit[0])] for _ in range(self.limit[1])]
        self.parent = None
        random.seed(datetime.now().timestamp())
        self.id = random
        self.life = 1260
        self.dir = dir.NORTH
        self.level = 1
        self.actions = []

    def speak(self, message: str) -> None:
        """
        This method makes the player speak.

        :param message: str - The message to be sent.
        :return: None
        """
        self.send_action(f"Broadcast {message}\n")

    def create_egg(self) -> None:
        """
        This method creates an egg.

        :return: None
        """
        self.send_action("Fork\n")

    def turn_around_without_watching(self) -> None:
        """
        This method makes the player turn around without watching.

        :return: None
        """
        self.right()
        self.right()
        self.actions.append('Right\n')
        self.actions.append('Right\n')

    def move_without_watching(self, dire: dir, right: dir, left: dir, turn_around: dir) -> None:
        """
        This method makes the player move without watching.

        :param dire: dir - The direction to move.
        :param right: dir - The right direction.
        :param left: dir - The left direction.
        :param turn_around: dir - The turn around direction.
        :return: None
        """
        self.actions.pop()
        if dire == right:
            self.right()
            self.actions.append('Right\n')
        elif dire == left:
            self.left()
            self.actions.append('Left\n')
        elif dire == turn_around:
            self.turn_around_without_watching()
        self.forward()
        self.actions.append('Forward\n')


    def move(self, mvt: list, dire: dir) -> None:
        """
        This method makes the player move.

        :param mvt: list - The movement to be done.
        :param dire: dir - The direction to move.
        :return: None
        """
        if mvt == []:
            return
        if self.pos[0] == mvt[0]:
            if self.pos[1] < mvt[1]:
                self.move_without_watching(dire, dir.NORTH, dir.SOUTH, dir.WEST)
            else:
                self.move_without_watching(dire, dir.SOUTH, dir.NORTH, dir.EAST)
        else:
            if self.pos[0] < mvt[0]:
                self.move_without_watching(dire, dir.EAST, dir.WEST, dir.SOUTH)
            else:
                self.move_without_watching(dire, dir.WEST, dir.EAST, dir.NORTH)

    def incantation(self) -> bool:
        """
        This method makes the player do an incantation.

        :return: bool - True if the incantation is done, False otherwise.
        """
        for i in self.goal:
            Path(self.limit, self.pos, (0, 0)).opti_path()
            for j in self.inv:
                if i[0] == j[0]:
                    self.send_action(f"Set {i[0]}\n")
        self.send_action("Incantation\n")
        return False

    def pos_view(self, axis: str, i: int, dire: dir) -> int:
        """
        This method returns the position of the view.

        :param axis: str - The axis to be used.
        :param i: int - The index.
        :param dire: dir - The direction.
        :return: int - The position of the view.
        """
        sense = 1
        if dire == dir.EAST or dire == dir.WEST:
            if axis == 'x':
                axis = 'y'
            else:
                axis = 'x'
        if dire == dir.SOUTH or dire == dir.WEST:
            sense = -1
        if axis == 'x':
            for j in range(0, 9):
                if i >= j * (j + 1) - j and i <= j * (j + 1) + j:
                    return sense * (i - j * (j + 1))
        elif axis == 'y':
            return sense * int(i ** 0.5)

    def update_map(self, view: list[str], dire: dir) -> None:
        """
        This method updates the map.

        :param view: list[str] - The view of the player.
        :param dire: dir - The direction of the player.
        :return: None
        """
        split_coma = view.split(',')
        for words in split_coma:
            split = words.split(' ')
            for i in range(len(split)):
                for obj in split:
                    if obj in self.goal.keys():
                        if obj not in self.map_knowledge[(self.pos[0] + self.pos_view('x', i, dire)) % self.limit[0]][(self.pos[1] + self.pos_view('y', i, dire)) % self.limit[1]]:
                            self.map_knowledge[(self.pos[0] + self.pos_view('x', i, dire)) % self.limit[0]][(self.pos[1] + self.pos_view('y', i, dire)) % self.limit[1]][obj] = 0
                        self.map_knowledge[(self.pos[0] + self.pos_view('x', i, dire)) % self.limit[0]][(self.pos[1] + self.pos_view('y', i, dire)) % self.limit[1]][obj] += 1
