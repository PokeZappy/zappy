from socket import socket

from ai.src.player.progenitor import Progenitor
from ai.src.player.incantator import Incantator
from ai.src.player.collector import Collector
from ai.src.player.pusher import Pusher
from ai.src.player.pnj import Pnj
from ai.src.player.first_born import First_born
from ai.src.player.north_guard import NorthGuard, ViceNorthGuard
from ai.src.player.hansel import Hansel
from ai.src.player.parrot import Parrot
from ai.src.player.inquisitor import Inquisitor

def is_all_val0(arg_dict, not_contains=None):
    """
    Check if all values in the dictionary are 0, excluding those specified in `not_contains`.

    :param arg_dict: Dictionary to check values.
    :param not_contains: List of values to exclude from the check.
    :return: True if all values are 0 or in `not_contains`, False otherwise.
    """
    if not_contains is None:
        not_contains = []
    values = arg_dict.values()
    for val in values:
        if val != 0 and val not in not_contains:
            return False
    return True

def role_enum(role: int, serv_info: list[int], cli_socket: socket, debug_mode: bool = False):
    """
    Get the role name from the integer value.

    :param int_val: Integer value of the role.
    :return: The role name.
    """
    match role:
        case 0: return Progenitor(serv_info, cli_socket, debug_mode)
        case 1: return Incantator(serv_info, cli_socket, debug_mode)
        case 2: return Collector(serv_info, cli_socket, debug_mode)
        case 3: return Pusher(serv_info, cli_socket, debug_mode)
        case 4: return Pnj(serv_info, cli_socket, debug_mode)
        case 5: return First_born(serv_info, cli_socket, debug_mode)
        case 6: return NorthGuard(serv_info, cli_socket, debug_mode)
        case 7: return Hansel(serv_info, cli_socket, debug_mode)
        case 8: return ViceNorthGuard(serv_info, cli_socket, debug_mode)
        case 12: return Parrot(serv_info, cli_socket, debug_mode)
        case 13: return Inquisitor(serv_info, cli_socket, debug_mode)
        case _: return None

