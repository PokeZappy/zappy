import re


def exctrat_direction(message: str) -> int:
    return int(message[8:9])


def get_infos(text: list[str]) -> tuple[list] | None:
    """
    Get information from the input text.

    Parameters:
    - text: a list of strings containing information.

    Returns:
    - A tuple of lists containing parsed information.
    """
    if len(text) == 2 and text[1][0:1].isnumeric() or len(text) < 2:
        return None, None
    if len(text) > 2:
        return tuple(zip(*(infos.split(";") for infos in text[2].split('~'))))
    return tuple(zip(*(infos.split(";") for infos in text[1].split('~'))))


def validate_look_pattern(s) -> bool:
    """
    Check if the input string matches a specific pattern.

    Parameters:
    s (str): The input string to be validated.

    Returns:
    int: 1 if the string matches the pattern, 0 otherwise.
    """
    pattern = r'^\[ player.*\]$'
    return True if re.match(pattern, s) else False


def validate_encryption_pattern(s) -> bool:
    """
    Validate if the input string follows a specific encryption pattern.

    Args:
        s (str): The input string to be validated.

    Returns:
        int: 0 if the pattern is valid, 1 if not.
    """
    pattern = r'^(?:\d+#){9}\d+(?:#(?:\d+#){9}\d+)*$'
    return False if re.fullmatch(pattern, s) else True


def validate_inventory_pattern(s) -> bool:
    """
    Validate if the input string matches a specific inventory pattern.

    Args:
        s (str): The input string to be validated.

    Returns:
        int: 1 if the input string matches the pattern, 0 otherwise.
    """
    pattern = r'^\[\s*food\s+\d+,\s+linemate\s+\d+,\s+deraumere\s+\d+,\s+sibur\s+\d+,\s+mendiane\s+\d+,\s+phiras\s+\d+,\s+thystame\s+\d+\s*\]$'
    return True if re.match(pattern, s) else False
