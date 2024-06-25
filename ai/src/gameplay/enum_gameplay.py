from enum import Enum
from dataclasses import dataclass


@dataclass
class Resources(Enum):
    NONE = 0
    LINEMATE = 1
    DERAUMERE = 2
    SIBUR = 3
    MENDIANE = 4
    PHIRAS = 5
    THYSTAME = 6
    FOOD = 7
    PLAYER = 8


@dataclass
class Directions(Enum):
    NORTH = 0
    EAST = 1
    SOUTH = 2
    WEST = 3

    def __add__(self, other):
        return (self.value + other) % 4

class RoleInGame(Enum):
    PROGENITOR = 0
    MASTERMIND = 1
    INCANTATOR = 2
    COLLECTOR = 3
    COOCKER = 4
    PUSHER = 5
    PNJ = 6
    FIRST_BORN = 7
    NORTH_GUARD = 8
    HANSEL = 9


TESTUDO = [
    {'id': 0, 'path': ['Forward']}, #Do not use
    {'id': 1, 'path': ['Forward']}, #Do not use
    {'id': 2, 'path': ['Forward']}, #Do not use
    {'id': 3, 'path': ['Forward']}, #Do not use
    {'id': 4, 'path': ['Forward', 'Forward']},
    {'id': 5, 'path': ['Forward', 'Right', 'Forward', 'Left', 'Forward']},
    {'id': 6, 'path': ['Forward', 'Right', 'Forward', 'Forward', 'Left', 'Forward']},
    {'id': 7, 'path': ['Forward', 'Left', 'Forward', 'Right', 'Forward']},
    {'id': 8, 'path': ['Forward', 'Left', 'Forward', 'Forward', 'Right', 'Forward']},
    {'id': 9, 'path': ['Forward', 'Left', 'Forward', 'Forward', 'Left', 'Forward', 'Forward', 'Forward', 'Left', 'Forward', 'Forward', 'Right']},
    {'id': 10, 'path': ['Forward', 'Left', 'Forward', 'Forward', 'Left', 'Forward', 'Forward', 'Left', 'Forward', 'Right']},
    {'id': 11, 'path': ['Forward', 'Left', 'Forward', 'Forward', 'Left', 'Forward', 'Forward', 'Forward', 'Left', 'Forward', 'Right']},
    {'id': 12, 'path': ['Forward', 'Left', 'Forward', 'Forward', 'Left', 'Forward', 'Forward', 'Forward']},
    {'id': 13, 'path': ['Forward', 'Left', 'Forward', 'Forward', 'Left', 'Forward', 'Forward']},
    {'id': 14, 'path': ['Forward', 'Left', 'Forward', 'Forward', 'Left', 'Forward']},
    {'id': 15, 'path': ['Forward', 'Left', 'Forward', 'Forward']},
    {'id': 16, 'path': ['Forward', 'Left', 'Forward']},
    {'id': 17, 'path': ['Forward', 'Right', 'Forward', 'Forward', 'Right', 'Forward', 'Forward', 'Forward', 'Right', 'Forward', 'Left']},
    {'id': 18, 'path': ['Forward', 'Right', 'Forward', 'Forward', 'Right', 'Forward', 'Forward', 'Forward']},
    {'id': 19, 'path': ['Forward', 'Right', 'Forward', 'Forward', 'Right', 'Forward', 'Forward', 'Right', 'Forward', 'Left']},
    {'id': 20, 'path': ['Forward', 'Right', 'Forward', 'Forward', 'Right', 'Forward', 'Forward']},
    {'id': 21, 'path': ['Forward', 'Right', 'Forward', 'Forward', 'Right', 'Forward']},
    {'id': 22, 'path': ['Forward', 'Right', 'Forward', 'Forward']},
    {'id': 23, 'path': ['Forward', 'Right', 'Forward']}
]

FOCUS = ['thystame', 'phiras', 'mendiane', 'deraumere', 'sibur', 'linemate']