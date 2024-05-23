/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** SocketExceptions.hpp
*/

#pragma once

#include <iostream>

class SocketException : public std::exception {
    public:
        const char *what() const noexcept override{ return "Unable to create socket"; };
};
class InvalidAdressException : public std::exception {
    public:
        const char *what() const noexcept override{ return "Invalid IP Address for the server."; };
};
class ServerConnectionException : public std::exception {
    public:
        const char *what() const noexcept override{ return "Unable to etablish connection to the server."; };
};