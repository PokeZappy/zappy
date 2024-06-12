
ressources = {'linemate': 0, 'deraumere': 0, 'sibur': 0, 'mendiane': 0, 'phiras': 0, 'thystame': 0, 'food': 0, 'player': 0}


def look_ressources(around: str, focus: list[str]) -> list[list[str]]:
    if len(around) < 8:
        return []
    my_list = around[8:-2].split(',')
    world_ressources = [tile.split() for tile in my_list]
    focus_ressources = []
    for tile in world_ressources:
        new_tile= []
        for items in tile:
            if items in focus:
                new_tile.append(items)
        focus_ressources.append(new_tile)
    return focus_ressources


def only_forward_resources(tiles: list[list[str]]) -> list[list[str]]:
    """

    """
    new_tiles: list[list[str]] = []
    if len(tiles) >= 4:
        new_tiles.append(tiles[0])
        new_tiles.append(tiles[2])
    if len(tiles) >= 9:
        new_tiles.append(tiles[6])
    if len(tiles) >= 16:
        new_tiles.append(tiles[12])
    if len(tiles) >= 25:
        new_tiles.append(tiles[20])
    if len(tiles) >= 36:
        new_tiles.append(tiles[30])
    if len(tiles) >= 49:
        new_tiles.append(tiles[42])
    if len(tiles) >= 64:
        new_tiles.append(tiles[56])
    if len(tiles) >= 81:
        new_tiles.append(tiles[72])
    return new_tiles
