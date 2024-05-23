/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** zappy_gui.cpp
*/

#include "GUI.hpp"
#include "SocketExceptions.hpp"
#include <sstream>

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

    void GUI::handleEvent(void)
    {
        sf::Event event;

        while (_window.pollEvent(event)) {
            switch (event.type) {
                case (sf::Event::Closed):
                    _window.close();
                    break;
                default: break;
            }
        }
    }

    void GUI::initTiles(void)
    {
        if (_mapX == -1 || _mapY == -1 || !_tiles.empty())
            return;
        for (int height = 0; height < _mapY; height++) {
            std::vector<Tile> horizontalVector;
            for (int width = 0; width < _mapX; width++) {
                horizontalVector.push_back(Tile());
            }
            _tiles.push_back(horizontalVector);
        }
    }

    void GUI::handleCommands(std::string &line)
    {
        int commandPos = line.find(' ');
        std::string command = line.substr(0, commandPos);
        std::string args = line.substr(commandPos + 1);
        std::istringstream ss(args);

        if (command == "msz") {
            ss >> _mapX >> _mapY;
            initTiles();
        }
    }

    void GUI::drawTiles(void)
    {
        if (_tiles.empty())
            return;
        double sizeWidth = static_cast<double>(GUI_WIDTH) / _tiles[0].size();
        double sizeHeight = static_cast<double>(GUI_HEIGHT) / _tiles.size();
        std::cout << sizeHeight << std::endl;

        for (size_t height = 0; height < _tiles.size(); height++) {
            for (size_t width = 0; width < _tiles[height].size(); width++) {
                sf::RectangleShape rectangle;
                rectangle.setSize(sf::Vector2f(sizeWidth, sizeHeight));
                rectangle.setPosition(width * sizeWidth, height * sizeHeight);
                rectangle.setFillColor(sf::Color::Black);
                rectangle.setOutlineColor(sf::Color::White);
                rectangle.setOutlineThickness(3.0);
                // std::cout << x * sizeHeight << " ," << y * sizeWidth << std::endl;
                _window.draw(rectangle);
            }
        }
    }

    void GUI::loop(void)
    {
        std::optional<std::string> command;
        while (_window.isOpen()) {
            _socket.receive();
            handleEvent();
            command = _socket.getNextCommand();
            while (command.has_value()) {
                handleCommands(command.value());
                command = _socket.getNextCommand();
            }
            drawTiles();
            _window.display();
        // std::cout << "RECEIVE BUFFER : " << _socket.getReceiveBuffer();
        }
    }
} // namespace Zappy
