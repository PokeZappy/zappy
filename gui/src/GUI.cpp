/*
** EPITECH PROJECT, 2024
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

    GUI::GUI(void) : _window(sf::VideoMode(GUI_WIDTH, GUI_HEIGHT), "GUI") {
        _view.setSize(GUI_WIDTH, GUI_HEIGHT);
        _view.setCenter(GUI_WIDTH / 2.f, GUI_HEIGHT / 2.f);
        _tileSelector.setFillColor(sf::Color::Transparent);
        _tileSelector.setOutlineColor(sf::Color::Red);
        _tileSelector.setOutlineThickness(3.0f);
    };

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
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
            _view.move(0.f, -_viewSpeed);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            _view.move(0.f, _viewSpeed);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
            _view.move(-_viewSpeed, 0.f);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            _view.move(_viewSpeed, 0.f);
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
        _tileWidth = static_cast<double>(GUI_WIDTH) / _tiles[0].size();
        _tileHeight = static_cast<double>(GUI_HEIGHT) / _tiles.size();
        _tileSelector.setSize(sf::Vector2f(_tileWidth, _tileHeight));
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

        for (size_t height = 0; height < _tiles.size(); height++) {
            for (size_t width = 0; width < _tiles[height].size(); width++) {
                sf::RectangleShape rectangle;
                rectangle.setSize(sf::Vector2f(_tileWidth, _tileHeight));
                rectangle.setPosition(width * _tileWidth, height * _tileHeight);
                rectangle.setFillColor(sf::Color::Black);
                rectangle.setOutlineColor(sf::Color::White);
                rectangle.setOutlineThickness(3.0);
                // std::cout << x * sizeHeight << " ," << y * sizeWidth << std::endl;
                _window.draw(rectangle);
            }
        }
    }

    void GUI::updateMouse(void)
    {
        _mousePositions.window = sf::Mouse::getPosition(_window);
        _window.setView(_view);
        _mousePositions.view = _window.mapPixelToCoords(_mousePositions.window);
        if (_mousePositions.view.x >= 0.0f && _tileWidth > 0.0f)
            _mousePositions.grid.x = _mousePositions.view.x / _tileWidth;
        if (_mousePositions.view.y >= 0.0f && _tileHeight > 0.0f)
            _mousePositions.grid.y = _mousePositions.view.y / _tileHeight;
        _tileSelector.setPosition(_mousePositions.grid.x * _tileWidth, _mousePositions.grid.y * _tileHeight);
    }

    void GUI::loop(void)
    {
        std::optional<std::string> command;

        while (_window.isOpen()) {
            _window.clear();
            _socket.receive(MSG_DONTWAIT);
            updateMouse();
            handleEvent();
            command = _socket.getNextCommand();
            while (command.has_value()) {
                handleCommands(command.value());
                command = _socket.getNextCommand();
            }
            drawTiles();
            if (!_tiles.empty())
                _window.draw(_tileSelector);
            // important de reset la view pour render tout ce qui n'est pas les tiles (overlay, text ...)
            _window.setView(_window.getDefaultView());
            _window.display();
        }
    }
} // namespace Zappy
