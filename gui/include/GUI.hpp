/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** zappy_gui.hpp
*/

#pragma once

#include <string.h>
#include <stdio.h>
#include <getopt.h>
#include "ClientSocket.hpp"

namespace Zappy {
    class GUI
    {
        private:
            int _port = -1;
            std::string _machine = "";
            int _socketFd = -1;
            ClientSocket _socket;
        public:
            GUI(void) = default;
            ~GUI(void) {
                if (_socketFd != -1)
                    close(_socketFd);
            }
            void setPort(int port) { _port = port; };
            void setMachine(std::string &machine) { _machine = machine; };
            int getPort(void) const { return (_port); }
            ClientSocket &getSocket(void) { return (_socket); }
            std::string &getMachine(void) { return (_machine); }
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
            void getOptions(int argc, char **argv);
    };
}
