/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** getOptions.cpp
*/

#include "Core.hpp"
#include "SocketExceptions.hpp"

namespace Zappy
{
    void Core::getOptions(int argc, char **argv)
    {
        int opt;

        while ((opt = getopt(argc, argv, "p:h:d")) != -1) {
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
            case 'd':
                _graphics = std::make_shared<Sfml>(_assetsRoot);
                break;
            default:
                throw InvalidOptionException(); break;
            }
        }
        if (_graphics == nullptr) {
            _graphics = std::make_shared<Raylib>(_assetsRoot);
        }
        if (_machine.empty() || _port == -1) {
            _machine = "127.0.0.1";
        }
    }
} // namespace Zappy
