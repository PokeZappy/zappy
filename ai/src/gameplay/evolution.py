from src.gameplay.enum_gameplay import Ressources as res

def evolution(level : int = 1):
    match level:
        case 1:
            return {"PLAYER": 1, "LINEMATE": 1}
        case 2:
            return {"PLAYER": 2, "LINEMATE": 1, "SIBUR": 1, "PHIRAS": 2}
        case 3:
            return {"PLAYER": 2, "LINEMATE": 2, "DERAUMERE": 1, "SIBUR": 1, "MENDIANE": 3}
        case 4:
            return {"PLAYER": 4, "LINEMATE": 1, "DERAUMERE": 1, "SIBUR": 2, "PHIRAS": 1}
        case 5:
            return {"PLAYER": 4, "LINEMATE": 1, "DERAUMERE": 2, "SIBUR": 1, "MENDIANE": 3}
        case 6:
            return {"PLAYER": 6, "LINEMATE": 1, "DERAUMERE": 2, "SIBUR": 3, "PHIRAS": 1}
        case 7:
            return {"PLAYER": 6, "LINEMATE": 2, "DERAUMERE": 2, "SIBUR": 2, "MENDIANE": 2, "PHIRAS": 2, "THYSTAME": 1}