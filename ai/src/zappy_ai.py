#!/usr/bin/env python3
import socket
import sys
from src.server import connexion


class Bot(object):
    """
    The Bot class is designed to interact with a server by sending specific action commands and managing the bot's state based on server information.
    """

    def __init__(self, serv_info: list[int], cli_socket: socket):
        """
        Initialize the Bot object with the client number and dimensions.

        Parameters:
        - serv_info: list[int] - Information about the server.
        - cli_socket: socket - The client socket for communication.

        This method initializes the Bot object with the provided client number and dimensions.
        """
        self.cli_num = serv_info[0]
        self.dimensions = serv_info[1:]
        self.cli_socket = cli_socket
        print(self.cli_num)
        print(self.dimensions)
        print(self.cli_socket)

    def send_action(self, action: str) -> None:
        """
        Send an action command to the server.

        :param action: The action command to be sent after validation.
        :return: None
        """
        self.cli_socket.send(action.encode())

    def recv_action(self) -> str:
        """
        Receive an action command from the server.

        :return: str - The received action command from the server.
        """
        return self.cli_socket.recv(1024).decode()

    def forward(self) -> None:
        """
        Sends a 'Forward' command to the server to move up one tile.
        :return: None
        """
        self.send_action("Forward\n")

    def right(self) -> None:
        """
        Sends a 'Right' command to the server to move the bot to turn 90° right.

        :return: None
        """
        self.send_action("Right\n")

    def left(self) -> None:
        """
        Sends a 'Left' command to the server to move the bot to turn 90° left.

        :return: None
        """
        self.send_action("Left\n")

    def look_around(self):
        """
        Send a 'Look' command to look around.

        :return: The view of the bot after looking around.
        """
        self.send_action("Look\n")
        return self.recv_action()


    def inventory(self) -> None:
        """
        Send a 'Inventory' command to check the inventory.

        :return: None
        """
        self.send_action("Inventory\n")

    def broadcast(self, msg: str) -> None:
        """
         Send a broadcast message to all bots.

         :param msg: str - The message to broadcast.
         :return: None
         """
        self.send_action(f"Broadcast {msg}\n")

    def nbr_of_slot(self) -> None:
        """
        Send a 'Connect_nbr' command to check the number of team unused slots.

        :return: None
        """
        self.send_action("Connect_nbr\n")

    def fork_player(self) -> None:
        """
        Fork a new player from the current player.

        This method sends a 'Fork' command to the server to create a new player.

        :return: None
        """
        self.send_action("Fork\n")

    def eject(self) -> None:
        """
        Eject the bot from its current position.

        This method sends an 'Eject' command to the server to remove the bot from its current position.

        :return: None
        """
        self.send_action("Eject\n")

    def take_obj(self, obj: str) -> None:
        """
        Take an object from the current tile.

        This method sends a 'Take object' command to the server to pick up an object from the current tile.

        :return: None
        """
        self.send_action(f"Take {obj}\n")

    def set_obj(self, obj: str) -> None:
        """
        Set the specified object on the current tile.

        :return: None
        """
        self.send_action(f"Set {obj}\n")

    def incantation(self) -> None:
        """
        Perform the incantation action on the server.

        This method sends an 'Incantation' command to the server to start the incantation process.

        :return: None
        """
        self.send_action("Incantation\n")


def display_help() -> 0:
    """

    :return:
    """
    print(f"USAGE: ./zappy_ai.py -p port -n name -h machine")
    return 0
