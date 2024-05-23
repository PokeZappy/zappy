/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** Socket.hpp
*/

#pragma once

#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include <iostream>

class ClientSocket {
    public:
        ClientSocket(int port, std::string &ip);
        ~ClientSocket() {
            if (_socketFd != -1)
                close(_socketFd);
            }
        int getFd(void) { return (_socketFd); }
        void send(std::string &data);
        void receive(int buffSize = 1);
    private:
        int _socketFd;
        struct sockaddr_in _socketProperties;
        int _port;
        std::string _ip;
        std::string _receiveBuffer;
};