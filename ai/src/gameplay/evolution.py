def evolution(level: int = 1) -> dict | None:
    """
    Calculate the evolution requirements based on the level.

    :param level: The level for which to calculate the evolution requirements.
    :return: A dictionary representing the evolution requirements for the given level.
    """
    levels = {
        1: {"player": 1, "linemate": 1},
        2: {"player": 2, "linemate": 1, "sibur": 1, "phiras": 2},
        3: {"player": 2, "linemate": 2, "deraumere": 1, "sibur": 1, "mendiane": 3},
        4: {"player": 4, "linemate": 1, "deraumere": 1, "sibur": 2, "phiras": 1},
        5: {"player": 4, "linemate": 1, "deraumere": 2, "sibur": 1, "mendiane": 3},
        6: {"player": 6, "linemate": 1, "deraumere": 2, "sibur": 3, "phiras": 1},
        7: {"player": 6, "linemate": 2, "deraumere": 2, "sibur": 2, "mendiane": 2, "phiras": 2, "thystame": 1}
    }
    return levels.get(level, None)
