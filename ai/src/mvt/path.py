from math import floor

from src.gameplay.enum_gameplay import Directions as face


class Path(object):
    """
    A class to calculate paths from start to end points.
    """
    def __init__(self, limit: tuple[int, int], start: tuple[int, int], end: tuple[int, int], facing: int = None) -> None:
        """
        Initialize the Path object with limit, start, end points, and facing direction.

        Args:
        - limit: A tuple representing the limits of the path.
        - start: A tuple representing the starting point.
        - end: A tuple representing the end point.
        - facing: An integer representing the initial facing direction.
        """
        self.limit = limit
        self.start = start
        self.end = end
        self.path = []
        self.facing = facing
        self.path_facing = []

    def calculate_paths(self) -> tuple[bool, bool, int, int, int, int]:
        """
        Calculate the paths to reach the end point from the start point.

        Returns:
        - A tuple containing information about the directions to move (west, north, northward, eastward, southward, westward).
        """
        west: bool = False
        if self.end[0] - self.start[0] >= 0:
            westward = self.end[0] - self.start[0]
            eastward = self.start[0] + self.limit[0] - self.end[0]
        else:
            westward = self.limit[0] - self.start[0] + self.end[0]
            eastward = self.start[0] - self.end[0]
        north: bool = False
        if self.end[1] - self.start[1] > 0:
            northward = self.end[1] - self.start[1]
            southward = self.start[1] + self.limit[1] - self.end[1]
        else:
            northward = self.end[1] + self.limit[1] - self.start[1]
            southward = self.start[1] - self.end[1]

        if westward < eastward:
            west = True
        if northward < southward:
            north = True
        return west, north, northward, eastward, southward, westward

    def get_path(self) -> list[str]:
        """
        Calculate the path to move from the start point to the end point based on the current facing direction.

        Returns:
        - A list of strings representing the directions to move.
        """
        west, north, northward, eastward, southward, westward = self.calculate_paths()
        if self.facing == face.EAST.value or self.facing == face.WEST.value:
            self.calculate_horizontal_path(west, north, northward, eastward, southward, westward)
        elif self.facing == face.NORTH.value or self.facing == face.SOUTH.value:
            self.calculate_vertical_path(west, north, northward, eastward, southward, westward)
        return self.turns()

    def calculate_horizontal_path(self, west, north, northward, eastward, southward, westward):
        """
        Calculate the horizontal path based on the provided directions.

        Args:
        - west: A boolean indicating if the path is towards the west.
        - north: A boolean indicating if the path is towards the north.
        - northward: An integer representing the distance to move northward.
        - eastward: An integer representing the distance to move eastward.
        - southward: An integer representing the distance to move southward.
        - westward: An integer representing the distance to move westward.
        """
        if west and eastward - 1 <= westward or not west:
            self.path = [['Forward' * eastward]]
            self.path_facing = [face.EAST.value]
        else:
            self.path = [['Forward' * westward]]
            self.path_facing = [face.WEST.value]
        if north:
            self.path += [['Forward'] * northward]
            self.path_facing += [face.NORTH.value]
        else:
            self.path += [['Forward'] * southward]
            self.path_facing += [face.SOUTH.value]

    def calculate_vertical_path(self, west, north, northward, eastward, southward, westward):
        """
        Calculate the vertical path based on the provided directions.

        Args:
        - west: A boolean indicating if the path is towards the west.
        - north: A boolean indicating if the path is towards the north.
        - northward: An integer representing the distance to move northward.
        - eastward: An integer representing the distance to move eastward.
        - southward: An integer representing the distance to move southward.
        - westward: An integer representing the distance to move westward.
        """
        if north and southward - 1 <= northward or not north:
            self.path_facing = [face.SOUTH.value]
            self.path = [['Forward'] * southward]
        else:
            self.path = [['Forward'] * northward]
            self.path_facing = [face.NORTH.value]
        if west:
            self.path += [['Forward'] * westward]
            self.path_facing += [face.WEST.value]
        else:
            self.path += [['Forward'] * eastward]
            self.path_facing += [face.EAST.value]

    def turns(self) -> list[str]:
        """
        Determine the necessary turns to align with the path direction.

        Returns:
        - A list of strings representing the turns to be made.
        """
        if self.facing in self.path_facing:
            return []
        self.path = self.path[::-1]
        self.path_facing = self.path_facing[::-1]
        if self.facing not in self.path_facing and 0 < self.facing < 3:
            if self.path_facing[0] > self.facing:
                self.path = ['Right'] + self.path
            else:
                self.path = ['Left'] + self.path
        elif self.facing not in self.path_facing and self.facing == 0 or self.facing == 3:
            if self.path_facing[0] > self.facing:
                self.path = ['Left'] + self.path
            else:
                self.path = ['Right'] + self.path
        if 0 < self.path_facing[0] < 3:
            if self.path_facing[1] > self.path_facing[0]:
                self.path.insert(len(self.path) - 1, 'Right')
            else:
                self.path.insert(len(self.path) - 1, 'Left')
        elif self.path_facing[0] == 0 or self.path_facing[0] == 3:
            if self.path_facing[1] > self.path_facing[0]:
                self.path.insert(len(self.path) - 1, 'Left')
            else:
                self.path.insert(len(self.path) - 1, 'Right')
        return self.path
