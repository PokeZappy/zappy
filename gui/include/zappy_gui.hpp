/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** zappy_gui.hpp
*/

#pragma once

#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <iostream>
#include <getopt.h>
#include <arpa/inet.h>
#include <sys/socket.h>

class ZappyGUI
{
    private:
        int _port = -1;
        std::string _machine = "";
    public:
        ZappyGUI(void) = default;
        ~ZappyGUI(void) = default;
        void setPort(int port) { _port = port; };
        void setMachine(std::string &machine) { _machine = machine; };
        int getPort(void) const { return (_port); }
        std::string getMachine(void) { return (_machine); }
        class InvalidOptionException : public std::exception {
                public:
                    const char *what() const noexcept override{ return "Invalid option in parsing"; };
        };
        class MissingOptionException : public std::exception {
                public:
                    const char *what() const noexcept override{ return "Missing exception in parsing"; };
        };
        class DoubleOptionException : public std::exception {
                public:
                    const char *what() const noexcept override{ return "Double option detected in parsing"; };
        };
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
        void getOptions(int argc, char **argv);
        void server_connect(void);
};
