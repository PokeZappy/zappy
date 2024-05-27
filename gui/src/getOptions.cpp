/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** getOptions.cpp
*/

#include "GUI.hpp"
#include "SocketExceptions.hpp"

namespace Zappy
{
    void GUI::getOptions(int argc, char **argv)
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
} // namespace Zappy
