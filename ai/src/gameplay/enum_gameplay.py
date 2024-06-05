from enum import Enum

class Ressources(Enum):
    NONE = 0
    LINEMATE = 1
    DERAUMERE = 2
    SIBUR = 3
    MENDIANE = 4
    PHIRAS = 5
    THYSTAME = 6
    FOOD = 7
    PLAYER = 8

class Directions(Enum):
    NORTH = 0
    EAST = 1
    SOUTH = 2
    WEST = 3

    def __add__(self, other):
        return (self.value + other) % 4
