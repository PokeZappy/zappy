from src.gameplay.enum_gameplay import Ressources as res

def evolution(level : int = 1):
    match level:
        case 1:
            return {"player": 1, "linemate": 1}
        case 2:
            return {"player": 2, "linemate": 1, "sibur": 1, "phiras": 2}
        case 3:
            return {"player": 2, "linemate": 2, "deraumere": 1, "sibur": 1, "mendiane": 3}
        case 4:
            return {"player": 4, "linemate": 1, "deraumere": 1, "sibur": 2, "phiras": 1}
        case 5:
            return {"player": 4, "linemate": 1, "deraumere": 2, "sibur": 1, "mendiane": 3}
        case 6:
            return {"player": 6, "linemate": 1, "deraumere": 2, "sibur": 3, "phiras": 1}
        case 7:
            return {"player": 6, "linemate": 2, "deraumere": 2, "sibur": 2, "mendiane": 2, "phiras": 2, "thystame": 1}