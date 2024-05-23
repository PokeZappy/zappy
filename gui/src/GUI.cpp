/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** zappy_gui.cpp
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

    void GUI::loop(void)
    {
        std::optional<std::string> command;
        while (1) {
            _socket.receive();
            command = _socket.getNextCommand();
            while (command.has_value()) {
                std::cout << command.value();
                command = _socket.getNextCommand();
            }
        // std::cout << "RECEIVE BUFFER : " << _socket.getReceiveBuffer();
        }
    }
} // namespace Zappy
