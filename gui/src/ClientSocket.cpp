/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** ClientSocket.cpp
*/

#include "ClientSocket.hpp"
#include "SocketExceptions.hpp"

void ClientSocket::connectSocket(int port, std::string &ip) {
    _port = port;
    _ip = ip;
    _socketFd = socket(AF_INET, SOCK_STREAM, 0);

    if (_socketFd < 0)
        throw SocketException();
    _socketProperties.sin_family = AF_INET;
    _socketProperties.sin_port = htons(_port);

    if (inet_pton(AF_INET, _ip.c_str(), &_socketProperties.sin_addr) <= 0)
        throw InvalidAdressException();
    if (connect(_socketFd, (struct sockaddr *)&_socketProperties, sizeof(_socketProperties)) < 0)
        throw ServerConnectionException();
    receive();
    if (_receiveBuffer != "WELCOME\n")
        throw ServerConnectionException();
    _receiveBuffer.clear();
    sendData("GRAPHIC\n");
}

void ClientSocket::receive(int flags)
{
    char buffer[BUFFER_SIZE] = {0};
    int valread = recv(_socketFd, buffer, sizeof(buffer) - 1, flags);

    // With MSG_DONTWAIT recv returns -1 whenever nothing is pending, which is the
    // common case; indexing the buffer with it would write out of bounds.
    if (valread <= 0)
        return;
    _receiveBuffer.append(buffer, valread);
}

void ClientSocket::sendData(std::string data)
{
    if (send(_socketFd, data.c_str(), data.size(), 0) == -1)
        throw ServerConnectionException();
}

std::optional<std::string> ClientSocket::getNextCommand(void)
{
    if (_receiveBuffer.empty())
        return std::nullopt;
    std::string command = _receiveBuffer.substr(0, _receiveBuffer.find('\n') + 1);
    if (!command.ends_with('\n'))
        return std::nullopt;
    _receiveBuffer = _receiveBuffer.erase(0, _receiveBuffer.find('\n') + 1);
    return command;
}
