// /*
// ** EPITECH PROJECT, 2024
// ** zappy
// ** File description:
// ** drawTiles.cpp
// */

// #include "Sfml.hpp"

// namespace Zappy
// {
//     void Sfml::drawTiles(void)
//     {
//         if (_tiles.empty())
//             return;

//         for (size_t height = 0; height < _tiles.size(); height++) {
//             for (size_t width = 0; width < _tiles[height].size(); width++) {
//                 sf::RectangleShape rectangle;
//                 rectangle.setSize(sf::Vector2f(_tileWidth, _tileHeight));
//                 rectangle.setPosition(width * _tileWidth, height * _tileHeight);
//                 rectangle.setFillColor(sf::Color::Black);
//                 rectangle.setOutlineColor(sf::Color::White);
//                 rectangle.setOutlineThickness(3.0);
//                 // std::cout << x * sizeHeight << " ," << y * sizeWidth << std::endl;
//                 _window.draw(rectangle);
//             }
//         }
//     }
// } // namespace Zappy
