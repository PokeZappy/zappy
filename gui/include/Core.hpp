/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Core.hpp
*/

#pragma once

#include <string.h>
#include <stdio.h>
#include <getopt.h>
#include "Tools.hpp"

#include "ClientSocket.hpp"
#include "Sfml.hpp"
#include "world/World.hpp"

namespace Zappy {
    class Core {
    public:
        Core() = default;
        ~Core() = default;
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
        void loop(void);
    private:
        int _port = -1;
        std::string _machine = "";
        ClientSocket _socket;
        Sfml _graphics;
        World _world;
    };
}