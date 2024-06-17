import socket

from ai.src.player.player import Player
from ai.src.utils.info_look import look_resources, only_forward_resources


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

    def go_to_start(self, index):
        #  TODO - pour chaque index on vient se placer sur une case en particulier pour pas tomber sur une ligne sans rien
        pass

    def raids_resources(self, tiles) -> None:
        """
        Perform raids on resources based on the given tiles and focus.

        Parameters:
        - tiles: list - List of tiles to search for resources.

        Returns:
        - None
        """
        for tile in tiles:
            for resource in tile:
                if resource in self.focus:
                    self.queue.append(("Take", resource))
            self.queue.append('Forward')

    def mouving_straight(self, index) -> None:
        """
        Move the player straight while focusing on specific resources.

        Parameters:
        - index: int - The index of the player.
        """
        self.go_to_start(index)
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

    def reset_focus(self) -> None:
        """
        Reset the focus of the player to default values.
        """
        self.focus = ['linemate', 'deraumere', 'sibur', 'mendiane', 'phiras', 'thystame', 'food']
        self.hard_focus = False
        self.nbr_focus = []

    def search_lvl_1(self, focus: list[str] = ['linemate', 'deraumere', 'sibur', 'mendiane', 'phiras', 'thystame', 'food']) -> None:
        # TODO : regarde puis tourne dans l'angle avec le plus de resources (sinon) par défaut droite
        #  regarde pour savoir s'il a un truc sur la case puis avance tourne avance ramasse avance ramasse, etc
        #  sortie de la boucle quand les resources sont toutes récup et pas besoin de chercher la nourriture.
        while True:
            self.check_inventory()
            self.recv_action()
            self.look_around()
            around: str = self.recv_action()
            vision_resources = look_resources(around, focus)
            for i in vision_resources[0]:
                if i in focus:
                    self.take_obj(i)
                    result = self.recv_action()
                    if result == 'ok':
                        self.inventory[i] += 1
        #     TODO : savoir si plus de resources à gauche qu'à droite
            if len(vision_resources[1]) == len(vision_resources[:-1]) == 0:
        #     tout droit
                self.forward()
                self.recv_action()
                for i in vision_resources[2]:
                    if i in focus:
                        self.take_obj(i)
                        result = self.recv_action()
                        if result == 'ok':
                            self.inventory[i] += 1
            elif len(vision_resources[1]) < len(vision_resources[-1]):
                self.left()
                self.recv_action()
                self.forward()
                self.recv_action()
                self.look_around()
                around = self.recv_action()
                tile = look_resources(around, focus)
                for i in tile[0]:
                    if i in focus:
                        self.take_obj(i)
                        result = self.recv_action()
                        if result == 'ok':
                            self.inventory[i] += 1
                self.right()
                self.recv_action()
                self.forward()
                self.recv_action()
                for i in vision_resources[-1]:
                    if i in focus:
                        self.take_obj(i)
                        result = self.recv_action()
                        if result == 'ok':
                            self.inventory[i] += 1
                self.forward()
                self.recv_action()
                for i in vision_resources[2]:
                    if i in focus:
                        self.take_obj(i)
                        result = self.recv_action()
                        if result == 'ok':
                            self.inventory[i] += 1
                self.forward()
                self.recv_action()
                for i in vision_resources[1]:
                    if i in focus:
                        self.take_obj(i)
                        result = self.recv_action()
                        if result == 'ok':
                            self.inventory[i] += 1
        #         gauche
            else:
                self.right()
                self.recv_action()
                self.forward()
                self.recv_action()
                self.look_around()
                around = self.recv_action()
                tile = look_resources(around, focus)
                for i in tile[0]:
                    if i in focus:
                        self.take_obj(i)
                        result = self.recv_action()
                        if result == 'ok':
                            self.inventory[i] += 1
                self.left()
                self.recv_action()
                self.forward()
                self.recv_action()
                for i in vision_resources[1]:
                    if i in focus:
                        self.take_obj(i)
                        result = self.recv_action()
                        if result == 'ok':
                            self.inventory[i] += 1
                self.forward()
                self.recv_action()
                for i in vision_resources[2]:
                    if i in focus:
                        self.take_obj(i)
                        result = self.recv_action()
                        if result == 'ok':
                            self.inventory[i] += 1
                self.forward()
                self.recv_action()
                for i in vision_resources[-1]:
                    if i in focus:
                        self.take_obj(i)
                        result = self.recv_action()
                        if result == 'ok':
                            self.inventory[i] += 1
        #         droite

    def deposits_resources(self):
        """
        Deposits the resources from the player's inventory.

        This method adds the resources to the queue for depositing.
        """
        for resource in self.inventory:
            if resource != 'food':
                self.queue.append([('Set', resource) for _ in range(self.inventory[resource])])
    #     TODO - @Matthias est-ce que je le fais sortir ici et comment tout droit ou avec un 180° ?

    def make_action(self) -> None:
        """
        Perform the next action based on the current state of the player.

        This method checks if there are pending actions, looks around if needed, and applies the next action in the queue.
        """
        if len(self.actions) >= 1:
            return
        print(self.looked)
        # if not self.looked and 'Look' not in self.queue:
        self.queue.append('Look')
        self.apply_action()
        if self.looked:
            if len(self.queue) == 0:
                self.mouving_straight(0)
            self.looked = False

    def broadcast_traitement(self, message: tuple | str) -> None:
        """
        Process the broadcast message and take appropriate actions.

        Parameters:
        - message: tuple | str - The message received for broadcast processing.
        """
        if message['msg'] == 'quid habes ut nobis offerat':
            self.message.buf_messages(self.inventory)
            self.broadcast()
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
        if message['msg'] == 'est dominus aquilonis':
            if self.path.facing is None:
                self.get_north(message['direction'])
        self.global_message()
