import socket
from abc import ABC

from src.player.player import Player
from src.utils.info_look import look_resources, only_forward_resources


class Collector(Player):

    def __init__(self, serv_info: list[int], cli_socket: socket, debug_mode: bool = False):
        super().__init__(serv_info, cli_socket, debug_mode)
        self.need_eat = 0
        self.pos = (0, 0)
        self.the_place_to_be = (0, 0)
        self.lvl = 1

    def go_to_start(self, index):
        #  TODO - pour chaque index on vient se placer sur une case en particulier pour pas tomber sur une ligne sans rien
        pass

    def raids_resources(self, tiles, focus) -> None:
        """

        """
        for tile in tiles:
            for resource in tile:
                if resource in focus:
                    self.take_obj(resource)
                    result = self.recv_action()
                    if result == 'ok':
                        self.inventory[resource] += 1
            self.forward()
            self.recv_action()
        self.check_inventory()
        self.recv_action()

    def mouving_straight(self, index, focus: list[str] = ['thystame', 'phiras', 'mendiane', 'deraumere', 'sibur', 'linemate', 'food']) -> None:
        """
        Move the player straight while focusing on specific resources.

        Parameters:
        - index: int - The index of the player.
        - focus: list[str] - List of resources to focus on while moving straight.
        """
        self.go_to_start(index)
        for _ in range(self.limit[0] + 1):
            self.look_around()
            tiles = self.recv_action()
            tiles = look_resources(tiles, focus)
            tiles = only_forward_resources(tiles)
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

    def run(self) -> None:
        # print(f'"{self.recv_action()}"')
        # self.recv_action()
        # self.search_lvl_1()
        self.mouving_straight(0)
