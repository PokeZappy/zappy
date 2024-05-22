/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** zappy_gui.cpp
*/

#include "zappy_gui.hpp"

void ZappyGUI::getOptions(int argc, char **argv)
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

void ZappyGUI::server_connect(void)
{
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in serv;

    if (sock < 0)
        throw SocketException();
    serv.sin_family = AF_INET;
    serv.sin_port = htons(_port);

    if (inet_pton(AF_INET, _machine.c_str(), &serv.sin_addr) <= 0)
        throw InvalidAdressException();
    if (connect(sock, (struct sockaddr *)&serv, sizeof(serv)) < 0)
        throw ServerConnectionException();

    char buffer[1024] = {0};
    int valread = recv(sock, buffer, sizeof(buffer) - 1, 0);
    if (valread < 0)
        throw ServerConnectionException();
    std::cout << buffer;
    // send(sock, "coucou", 6, 0);
    close(sock);
}