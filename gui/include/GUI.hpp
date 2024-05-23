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
#include <SFML/Graphics.hpp>
#include "Tile.hpp"

namespace Zappy {
    class GUI
    {
        #define GUI_WIDTH 1920
        #define GUI_HEIGHT 600
        private:
            int _port = -1;
            std::string _machine = "";
            ClientSocket _socket;
            sf::RenderWindow _window;
            int _mapX = -1;
            int _mapY = -1;
            std::vector<std::vector<Zappy::Tile>> _tiles;
        public:
            GUI(void) : _window(sf::VideoMode(GUI_WIDTH, GUI_HEIGHT), "GUI") {};
            ~GUI(void) = default;
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
            void handleEvent(void);
            void handleCommands(std::string &line);
            void initTiles(void);
            void drawTiles(void);
    };
}
