import socket

from src.player.player import Player
from src.utils.info_look import look_resources, only_forward_resources


class Collector(Player):

    def __init__(self, serv_info: list[int], cli_socket: socket, debug_mode: bool = False):
        super().__init__(serv_info, cli_socket, debug_mode)
        self.need_eat = 0
        self.pos: tuple[int, int] = (0, 0)
        self.the_place_to_be: tuple[int, int] = (0, 0)
        self.focus = None
        self.depot: tuple[int, int] = (0, 0)
        self.hard_focus: bool = False

    def go_to_start(self, index):
        #  TODO - pour chaque index on vient se placer sur une case en particulier pour pas tomber sur une ligne sans rien
        pass

    def raids_resources(self, tiles, focus) -> None:
        """

        """
        for tile in tiles:
            for resource in tile:
                if resource in focus:
                    self.queue.append(("Take", resource))
            self.queue.append('Forward')

    def mouving_straight(self, index, focus: list[str] = ['thystame', 'phiras', 'mendiane', 'deraumere', 'sibur', 'linemate', 'food']) -> None:
        """
        Move the player straight while focusing on specific resources.

        Parameters:
        - index: int - The index of the player.
        - focus: list[str] - List of resources to focus on while moving straight.
        """
        self.go_to_start(index)
        # self.look_around()

        # while self.look == "":
        #     tiles = self.look
        # tiles = self.recv_action()
        tiles = look_resources(self.environment, focus)
        self.looked = False
        self.environment = ""
        tiles = only_forward_resources(tiles)
        print(f'FORWARD tiles {tiles}')
        self.raids_resources(tiles, focus)
    #         TODO - check if food needed -> search_food()

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

    def search_food(self) -> None:
        self.search_lvl_1('food')

    def make_action(self) -> None:
        if len(self.actions) >= 1:
            return
        print(self.looked)
        if not self.looked and 'Look' not in self.queue:
            self.queue.append('Look')
        if self.looked:
            if len(self.queue) == 0:
                self.mouving_straight(0)
            self.looked = False
        self.apply_action()

    def broadcast_traitement(self, message: tuple | str) -> None:
        if message['msg'] == 'quid habes ut nobis offerat':
            # TODO: send all inventory
            self.message.buf_messages(self.inventory)
            self.broadcast()
        if message['msg'] == 'focus in his opibus : ':
            self.focus = message['infos']
            print(message)
        #     TODO - actualiser le focus sur ces ressources
        if message['msg'] == 'collectio rerum : ':
            self.depot = message['coord']
            #TODO: point de dépot
        if message['msg'] == 'vade ad me aliquid : ':
            #TODO: ask for a hard focus ressource RETURN TO depot after taking the obj
            # TODOO - Parser le infos pour extraire les données comme nom et nombre
            self.focus = message['infos']
            # self.nbr_focus =
            self.hard_focus = True
        if message['msg'] == 'Potes dominum facti':
        #     TODO - validation passage pousseur pour aller au dépot
            # TODO - Déposer les ressources sur la case de dépot
            pass
        self.global_message()
