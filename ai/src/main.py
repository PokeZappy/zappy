#!/bin/python3

import sys
from src.server import connexion
from src.player.role import Role

from src.zappy_ai import display_help

def main():
    """
    The main function is the entry point of the program.

    :return: sys.exit 0 or 84(error)
    """
    try:
        if len(sys.argv) == 2 and sys.argv[1] == '--help':
            return display_help()
        if (len(sys.argv) != 5 and len(sys.argv) != 7):
            raise ValueError
        name = ""
        port = ""
        machine = ""
        for i in range(1, len(sys.argv), 2):
            if sys.argv[i] == '-p':
                port = sys.argv[i + 1]
            if sys.argv[i] == '-n':
                name = sys.argv[i + 1]
            if sys.argv[i] == '-h':
                machine = sys.argv[i + 1]
        server_info, cli_socket = connexion.connect(port, name, machine)
        mybot = Role(server_info, cli_socket)
        mybot.run()
    except (ValueError, AssertionError) as e:
        print(f"NOP: {e}")
        return 84
    return 0

if __name__ == "__main__":
    main()