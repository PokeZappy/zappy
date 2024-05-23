/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** ClientSocket.cpp
*/

#include "ClientSocket.hpp"
#include "SocketExceptions.hpp"

ClientSocket::ClientSocket(int port, std::string &ip) : _port(port), _ip(ip){
    _socketFd = socket(AF_INET, SOCK_STREAM, 0);

    if (_socketFd < 0)
        throw SocketException();
    _socketProperties.sin_family = AF_INET;
    _socketProperties.sin_port = htons(_port);

    if (inet_pton(AF_INET, _ip.c_str(), &_socketProperties.sin_addr) <= 0)
    if (connect(_socketFd, (struct sockaddr *)&_socketProperties, sizeof(_socketProperties)) < 0)
        throw ServerConnectionException();
}

void ClientSocket::receive(int buffSize = 1)
{
    char buffer[1024] = {0};
    int valread = recv(_socketFd, buffer, sizeof(buffer) - 1, 0);
    if (valread < 0)
        throw ServerConnectionException();
    std::cout << buffer << std::endl;
}