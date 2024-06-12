import socket
from abc import ABC

from src.player.player import Player
from src.mvt import path
from src.utils.info_look import look_resources


class Depot(Player):

    def __init__(self, serv_info: list[int], cli_socket: socket, debug_mode: bool = False):
        super().__init__(serv_info, cli_socket, debug_mode)
        self.need_eat = 0
        self.pos = (0, 0)
        self.the_place_to_be = (0, 0)
        self.incantation_loc = (0, 0)
        self.path = path.Path(limit=self.limit, start=self.pos, end=self.the_place_to_be, facing=self.dir)

    def updating_positions(self, start: tuple[int, int]= (-1, -1), end: tuple[int, int]= (-1, -1)) -> None:
        """
        Update the current position of the player based on the given start and end positions.

        :param start: Tuple representing the starting position. Default is (-1, -1).
        :param end: Tuple representing the target position. Default is (-1, -1).
        :return: None
        """
        if start != (-1, -1):
            self.pos = start
        if end != (-1, -1):
            self.the_place_to_be = end

    def delivery(self) -> None:
        # TODO - fait les allers retour just à changer les valeurs
        #  TODO - check if value is update or not
        #   self.path.start = self.pos
        #   self.path.end = self.the_place_to_be
        #   self.path.faciong = self.dir
        self.path.get_path()

    def taking_all(self) -> None:
        """
        Perform a comprehensive action of looking around, receiving tiles, and raiding resources.

        Returns:
        - None
        """
        self.look_around()
        tiles = self.recv_action()
        self.raids_resources(tiles[0])

    def raids_resources(self, tile, focus: list[str] = ['linemate', 'deraumere', 'sibur', 'mendiane', 'phiras', 'thystame', 'food']) -> None:
        # TODO duplaction de la methode de la classe Collector mais modifiée
        """
        Raids resources from a given tile based on the specified focus.

        This method iterates over the resources in the tile and collects them based on the focus list.

        Parameters:
        - tile: list - The tile containing resources.
        - focus: list - The list of resources to focus on.

        Returns:
        - None
        """
        for resource in tile:
            if resource in focus:
                self.take_obj(resource)
                result = self.recv_action()
                if result == 'ok':
                    self.inventory[resource] += 1

    def give_incantation_resources(self, focus: list[str] = ['linemate', 'deraumere', 'sibur', 'mendiane', 'phiras', 'thystame']) -> None:
        """
        Gives resources for the incantation process based on the specified focus.

        Parameters:
        - focus: list[str] - The list of resources to focus on during the incantation.

        Returns:
        - None
        """
        for resource in self.inventory:
            if resource in focus:
                self.set_obj(resource)
        self.message.buf_messages('facultates positas carmina')
        self.broadcast()
