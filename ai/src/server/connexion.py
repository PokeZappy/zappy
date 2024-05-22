import socket


def connect(port: str, team_name: str, host: str) -> tuple[list[int], socket]:
    """
    The connect function establishes a TCP connection to a specified host and port, sends a team name, and processes the received data into a list of integers, returning this list along with the socket object.

    :param port: The port number to connect to.
    :param team_name: A string representing the name of the team.
    :param host: The hostname or IP address to connect to.
    :return: A tuple containing a list of integers and the socket object used for the connection.
    """
    client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    client_socket.connect((host, int(port)))
    welcome_message = client_socket.recv(1024).decode().strip()
    print(f"Received: {welcome_message}")
    client_socket.send(f"{team_name}\n".encode())
    cli_number = client_socket.recv(1024).decode()
    print(f"Received: {cli_number}")
    new = cli_number.split()
    print(new)
    result = list(map(int, filter(None, new)))
    print(result)
    return result, client_socket
