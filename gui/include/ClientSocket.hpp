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
    #define BUFFER_SIZE 1024

    public:
        ClientSocket() {};
        ~ClientSocket() {
            if (_socketFd != -1)
                close(_socketFd);
            }
        void connectSocket(int port, std::string &ip);
        int getFd(void) { return (_socketFd); }
        void sendData(std::string data);
        void receive(void);
        std::optional<std::string> getNextCommand(void);
    private:
        int _socketFd;
        struct sockaddr_in _socketProperties;
        int _port;
        std::string _ip;
        std::string _receiveBuffer;
};
