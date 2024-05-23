/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** zappy_gui.cpp
*/

#include "GUI.hpp"
#include "SocketExceptions.hpp"

void Zappy::GUI::getOptions(int argc, char **argv)
{
    int opt;

    while ((opt = getopt(argc, argv, "p:h:")) != -1) {
        switch (opt) {
            case 'p':
                if (_port != -1)
                    throw DoubleOptionException();
                _port = std::stoi(optarg);
                break;
            case 'h':
                if (_machine != "")
                    throw DoubleOptionException();
                _machine = optarg;
                break;
            default:
                throw InvalidOptionException(); break;
        }
    }
    if (_machine.empty() || _port == -1) {
        throw MissingOptionException();
    }
}

// void Zappy::GUI::server_connect(void)
// {
//     _socket = ClientSocket(_port, _machine);
    // _socketFd = socket(AF_INET, SOCK_STREAM, 0);
    // struct sockaddr_in serv;

    // if (_socketFd < 0)
    //     throw SocketException();
    // serv.sin_family = AF_INET;
    // serv.sin_port = htons(_port);

    // if (inet_pton(AF_INET, _machine.c_str(), &serv.sin_addr) <= 0)
    // if (connect(_socketFd, (struct sockaddr *)&serv, sizeof(serv)) < 0)
    //     throw ServerConnectionException();

    // char buffer[1024] = {0};
    // int valread = recv(_socketFd, buffer, sizeof(buffer) - 1, 0);
    // // if (valread < 0)
    // //     throw ServerConnectionException();
    // std::cout << buffer << std::endl;
    // if (send(_socketFd, "GRAPHIC\n", 8, 0) == -1)
    //     std::cerr << "erreur" << std::endl;
    // char new_buffer[20] = {0};
    // valread = recv(_socketFd, new_buffer, sizeof(new_buffer) - 1, 0);
    // std::cout << new_buffer << std::endl << std::endl;
    // valread = recv(_socketFd, new_buffer, sizeof(new_buffer) - 1, 0);
    // std::cout << new_buffer << std::endl;
// }
