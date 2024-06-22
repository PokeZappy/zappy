/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** ClientSocket.hpp
*/

#pragma once

#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include <iostream>
#include <optional>

class ClientSocket {
    #define BUFFER_SIZE 262143

    public:
        ClientSocket() {};
        ~ClientSocket() {
            if (_socketFd != -1)
                close(_socketFd);
            }
        void connectSocket(int port, std::string &ip);
        int getFd(void) { return (_socketFd); }
        void sendData(std::string data);
        void receive(int flags = 0);
        std::optional<std::string> getNextCommand(void);
        std::string getReceiveBuffer(void) { return (_receiveBuffer); }
    private:
        int _socketFd;
        struct sockaddr_in _socketProperties;
        int _port;
        std::string _ip;
        std::string _receiveBuffer;
};
