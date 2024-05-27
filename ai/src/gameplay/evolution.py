from ressources import ressources as res

def evolution(level : int = 1):
    match level:
        case 1:
            return [(res.PLAYER, 1), (res.LINEMATE, 1)]
        case 2:
            return [(res.PLAYER, 2), (res.LINEMATE, 1), (res.DERAUMERE, 1), (res.SIBUR, 1)]
        case 3:
            return [(res.PLAYER, 2), (res.LINEMATE, 1), (res.SIBUR, 1), (res.PHIRAS, 2)]
        case 4:
            return [(res.PLAYER, 4), (res.LINEMATE, 1), (res.DERAUMERE, 1), (res.SIBUR, 2), (res.PHIRAS, 1)]
        case 5:
            return [(res.PLAYER, 4), (res.LINEMATE, 1), (res.DERAUMERE, 2), (res.SIBUR, 1), (res.MENDIANE, 3)]
        case 6:
            return [(res.PLAYER, 6), (res.LINEMATE, 1), (res.DERAUMERE, 2), (res.SIBUR, 3), (res.PHIRAS, 1)]
        case 7:
            return [(res.PLAYER, 6), (res.LINEMATE, 2), (res.DERAUMERE, 2), (res.SIBUR, 2), (res.MENDIANE, 2), (res.PHIRAS, 2), (res.THYSTAME, 1)]