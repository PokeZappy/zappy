import socket
import time

from ai.src.player.player import Player
from ai.src.utils.info_look import look_resources, only_forward_resources
from ai.src.gameplay.enum_gameplay import Directions as compass


class Collector(Player):

    def __init__(self, serv_info: list[int], cli_socket: socket, debug_mode: bool = False):
        super().__init__(serv_info, cli_socket, debug_mode)
        self.need_eat = 0
        self.pos: tuple[int, int] = (0, 0)
        self.the_place_to_be: tuple[int, int] = (0, 0)
        self.focus: list[str] = ['thystame', 'phiras', 'mendiane', 'deraumere', 'sibur', 'linemate', 'food']
        self.nbr_focus: list[int] = [0]
        self.depot: tuple[int, int] = (0, 0)
        self.hard_focus: bool = False
        self.response: int = 0
        self.id = 0
        self.get_id('Quot publicani ibi sunt?')

    def go_to_start(self) -> None:
        # TODO - faire un algo qui vient placer le collecteur en fonction de son id % taille max de la map pour éviter les bétise sur le 0 1 et 2
        if self.id == 0:
            return self.queue.append('Forward')
        if self.id % 2 == 0:
            self.path.start = (0, 0)
            self.path.end = (1, self.id / 2)
            print(self.path.get_path())
        else:
            self.path.start = (0, 0)
            self.path.end = (1, self.path.min_limit - self.id // 2)
            print(self.path.get_path())

    def raids_resources(self, tiles) -> None:
        """
        Perform raids on resources based on the given tiles and focus.

        :param tiles: list - List of tiles to search for resources.
        :return: None
        """
        for tile in tiles:
            for resource in tile:
                if resource in self.focus:
                    self.queue.append(("Take", resource))
            self.queue.append('Forward')

    def mouving_straight(self,) -> None:
        """
        Move the player straight while focusing on specific resources.

        :return: None
        """
        tiles = look_resources(self.environment, self.focus)
        self.looked = False
        self.environment = ""
        tiles = only_forward_resources(tiles)
        print(f'FORWARD tiles {tiles}')
        self.raids_resources(tiles)
        if self.hard_focus and self.nbr_focus[0] <= self.inventory[self.focus[0]]:
            # TODO - go to depot à voir avec @Matthias
            self.move_to(self.depot)
        # TODO - check if food needed -> search_food()
        #  sécu si pas de bouffe sur le chemin.

    def reset_focus(self) -> None:
        """
        Reset the focus of the player to default values.

        :return: None
        """
        self.focus = ['linemate', 'deraumere', 'sibur', 'mendiane', 'phiras', 'thystame', 'food']
        self.hard_focus = False
        self.nbr_focus = []

    def deposits_resources(self) -> None:
        """
        Deposits the resources from the player's inventory.
        This method adds the resources to the queue for depositing and remove it from the inventory.

        :return: None
        """
        for resource in self.inventory:
            if resource != 'food':
                self.queue.append([('Set', resource) for _ in range(self.inventory[resource])])
                self.inventory[resource] -= 1
    #     TODO - sortie vers le nord

    def make_action(self) -> None:
        """
        Perform the next action based on the current state of the player.
        This method checks if there are pending actions, looks around if needed, and applies the next action in the queue.

        :return: None
        """
        if len(self.queue) > 0:
            self.apply_action()
        if len(self.actions) > 0:
            return
        if not self.looked and 'Look' not in self.queue and self.path.facing is not None:
            self.queue.append('Look')
        if self.looked:
            if len(self.queue) == 0:
                self.mouving_straight()
            self.looked = False

    def broadcast_traitement(self, message: tuple | str) -> None:
        """
        Process the broadcast message and take appropriate actions.

        :param message: tuple | str - The message received for broadcast processing.
        :return: None
        """
        if message['msg'] == 'quid habes ut nobis offerat':
            self.message.buf_messages(self.inventory)
            self.queue.append('Broadcast')
        if message['msg'] == 'focus in his opibus : ':
            self.focus = message['infos']
            self.nbr_focus = message['nbr']
        #     TODO clear la queue
        if message['msg'] == 'collectio rerum : ':
            self.depot = message['coord']
        if message['msg'] == 'vade ad me aliquid : ':
        #     TODO - clear la queue
            self.focus = message['infos']
            self.nbr_focus = message['nbr']
            self.hard_focus = True
        if message['msg'] == 'Potes dominum facti':
            self.queue.append('Forward')
            self.queue.append('Forward')
            self.deposits_resources()
        #     TODO - on peut y mettre dans globale message
        if message['msg'] == 'est dominus aquilonis' and self.path.facing is None:
            self.get_north(message['direction'])
            self.turn_to_the_north()
            self.go_to_start()
        if message['msg'] == 'Ego sum publicani ibi' and not self.got_id:
            # TODO - ADD parser id to replace missing id if collector died
            self.id += 1
            print(self.id)
        if message['msg'] == 'Quot publicani ibi sunt?':
            self.message.buf_messages('Ego sum publicani ibi', infos=[self.id])
            self.queue.insert(0, 'Broadcast')
        self.global_message()
