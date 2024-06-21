import socket
import select
import random
from abc import abstractmethod
from datetime import datetime

from ai.src.zappy_ai import Bot
from ai.src.gameplay.enum_gameplay import Directions as dir
from ai.src.mvt.path import Path
from ai.src.gameplay.enum_gameplay import Resources as res
from ai.src.utils.info_look import look_resources


class Player(Bot):
    def __init__(self, serv_info: list[int], cli_socket: socket, debug_mode: bool = False):
        """
        This class is the player class.
        
        :param serv_info: list[int] - Information about the server.
        :param cli_socket: socket - The client socket for communication.
        :param debug_mode: bool - The debug mode.
        """
        super().__init__(serv_info, cli_socket, debug_mode)
        self.limit: list[int] = self.dimensions
        self.pos: list[int] = [0, 0]
        self.inv = {}
        self.parent = None
        self.level: int = 1
        self.actions = []
        self.queue = []
        self.LIMIT_QUEUE: int = 10
        self.LEVEL_MAX: int = 8
        self.FORK_ACTION: int = 42
        self.INCUBATION_TIME: int = 600
        self.inventory: dict[str: int] = {'food': 10,
                                          'linemate': 0,
                                          'deraumere': 0,
                                          'sibur': 0,
                                          'mendiane': 0,
                                          'phiras': 0,
                                          'thystame': 0
                                          }
        self.looked: bool = False
        self.environment: str = ""
        self.path = Path(self.limit, (0, 0), (0, 0))
        self.got_id: int = 0
        # self.got_id: bool = False

        #TODO: seed is it necessary?
        random.seed(datetime.now().timestamp())
        self.id = random

        self.life = 126 * self.inventory['food']
    
        #TODO: improve the direction system
        self.dir = dir.NORTH

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

    def move(self, mvt: list | tuple, dire: dir) -> None:
        """
        This method makes the player move.

        :param mvt: list - The movement to be done.
        :param dire: dir - The direction to move.
        :return: None
        """
        if not mvt:
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

    def get_north(self, direction: int):
        """
        Set the player's facing direction based on the input direction.

        :param direction: int - The direction value to set the player's facing direction.
        """
        if direction == 1:
            self.path.facing = dir.NORTH.value
        if direction == 5:
            self.path.facing = dir.SOUTH.value
        if direction == 3:
            self.path.facing = dir.EAST.value
        if direction == 7:
            self.path.facing = dir.WEST.value

    def turn_to_the_north(self) -> None:
        """
        Turn the player to face the North direction.

        This method checks the current facing direction of the player and adjusts it to face North if needed.

        :return: None
        """
        # TODO - move it in Path class if possible
        if self.debug_mode:
            print('going to the north')
        if self.path.facing == dir.NORTH.value:
            return
        if self.path.facing == dir.EAST.value:
            self.queue.append('Left')
            self.path.facing = dir.NORTH.value
        if self.path.facing == dir.WEST.value:
            self.queue.append('Right')
            self.path.facing = dir.NORTH.value
        if self.path.facing == dir.SOUTH.value:
            self.queue.append('Right')
            self.queue.append('Right')
            self.path.facing = dir.NORTH.value

    def move_to(self, pos: tuple[int, int]) -> None:
        """
        This method makes the player move to a position.

        :param pos: tuple[int, int] - The position to move to.
        :return: None
        """
        path = Path(self.limit, self.pos, pos, self.dir).opti_path()
        for mvt in path:
            self.queue.append(mvt)

    def get_id(self, message: str) -> None:
        self.message.buf_messages(message)
        self.queue.append('Broadcast')
        self.queue.append(('Take', 'player'))
        self.queue.append(('Take', 'player'))
        self.queue.append(('Take', 'player'))

    def apply_action(self) -> None:
        """
        This method applies the action to the player.

        :return: None
        """
        self.actions.append(self.queue[0])
        self.queue.pop(0)
        if self.debug_mode:
            print(f'apply action actions: {self.actions}')
            print(f'waiting queue: {self.queue}')
        action = self.actions[-1]
        if action[0] == 'Take':
            self.take_obj(action[1])
        elif action == 'Incantation':
            self.incantation()
        elif action[0] == 'Set':
            self.set_obj(action[1])
        elif action == 'Look':
            self.look_around()
        elif action == 'Fork':
            self.create_egg()
        elif action == 'Slots':
            self.nbr_of_slot()
        elif action == 'Broadcast':
            self.broadcast()
        elif action == 'Forward':
            self.forward()
        elif action == 'Right':
            self.right()
        elif action == 'Left':
            self.left()
        elif action == 'Inventory':
            self.check_inventory()
        elif isinstance(action, tuple):
            self.move(action, self.dir)

    def recv_treatment(self, buf) -> None:
        """
        Process the received data from the server.

        This method handles the data received from the server, updates player attributes accordingly, and removes the processed action from the action queue.

        :param buf: The data received from the server.
        :return: None
        """
        if len(self.actions) == 0:
            recv_list = self.message.receive(buf)
        else:
            recv_list = self.message.receive(buf, self.actions[0])
        for recv_type, msgs in recv_list:
            if recv_type == 'ko' and len(self.actions) > 0 and self.actions[0] == ('Take', 'player'):
                self.got_id += 1
            if recv_type == 'ok':
                if isinstance(msgs, tuple) and msgs[0] == 'Take' and msgs[1] != 'player':
                    self.inventory[msgs[1]] += 1
                    if msgs[1] == 'food':
                        self.life += self.FOOD
                if isinstance(msgs, tuple) and msgs[0] == 'Set':
                    self.inventory[msgs[1]] -= 1
            if recv_type == 'look':
                self.looked = True
                self.environment = msgs
            if recv_type == 'inventory':
                print("inventory")
            if recv_type == 'broadcast':
                for msg in msgs:
                    self.broadcast_traitement(msg)
                continue
            if len(self.actions) != 0:
                self.actions.pop(0)

    @abstractmethod
    def make_action(self) -> None:
        pass

    def update_inventory(self, new_object: str, action: bool) -> None:
        """
        TODO - doit être appelé quand on vient récup un obt
        """
        if action:
            self.inventory[new_object] += 1
        else:
            self.inventory[new_object] -= 1

    def run(self) -> None:
        """
        This method is the main loop of the ai.

        :return: None
        """
        while self.level < self.LEVEL_MAX:
            infds, outfds, _ = select.select(self.inout, self.inout, [])

            """
            infds: list[socket] - The list of sockets to read from.
            """
            if len(infds) != 0:
                buf = self.recv_action()
                self.recv_treatment(buf)

            """
            outfds: list[socket] - The list of sockets to write to.
            """
            if len(outfds) != 0 and len(self.actions) < self.LIMIT_QUEUE:
                self.make_action()

    @abstractmethod
    def broadcast_traitement(self, msg: tuple | str) -> None:
        pass

    def global_message(self) -> None:
        # TODO - faire les messages globaux comme le changement de metier
        pass
