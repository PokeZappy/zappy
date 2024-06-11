from src.gameplay.enum_gameplay import Ressources as res

def is_all_val0(dict, not_contains = []):
    values = dict.values()
    for val in values:
        if val != 0 and val not in not_contains:
            return False
    return True

