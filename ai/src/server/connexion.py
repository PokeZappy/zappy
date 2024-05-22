import socket
import re


def connect(port, team_name, host) -> list[int]:
    client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    client_socket.connect((host, int(port)))
    welcome_message = client_socket.recv(1024).decode().strip()
    print(f"Received: {welcome_message}")
    client_socket.send(f"{team_name}\n".encode())
    cli_number = client_socket.recv(1024).decode()
    print(f"Received: {cli_number}")
    new = re.split(' |\\n', cli_number)
    print(new)
    result = [int(x) for x in new if x != '']
    print(result)
    return result
