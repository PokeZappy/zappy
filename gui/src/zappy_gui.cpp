/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** zappy_gui.cpp
*/

#include "zappy_gui.hpp"

void ZappyGUI::getOptions(int argc, char **argv)
{
    int opt;

    while ((opt = getopt(argc, argv, "p:h:")) != -1) {
        switch (opt) {
            case 'p':
                _port = std::stoi(optarg);
                break;
            case 'h':
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