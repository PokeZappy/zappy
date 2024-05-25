/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Tile.hpp
*/

#pragma once

#include <iostream>

namespace Zappy {
    class Tile {
        public:
            Tile() = default;
            ~Tile() = default;
            size_t getFood(void) { return (_food); }
            size_t getLinemate(void) { return (_linemate); }
            size_t getDeraumere(void) { return (_deraumere); }
            size_t getSibur(void) { return (_sibur); }
            size_t getMendiane(void) { return (_mendiane); }
            size_t getPhiras(void) { return (_phiras); }
            size_t getThystame(void) { return (_thystame); }
            size_t getPlayers(void) { return (_players); }
            size_t getEggs(void) { return (_eggs); }
            void setFood(size_t food) { _food = food; }
            void setLinemate(size_t linemate) { _linemate = linemate; }
            void setDeraumere(size_t deraumere) { _deraumere = deraumere; }
            void setSibur(size_t sibur) { _sibur = sibur; }
            void setMendiane(size_t mendiane) { _mendiane = mendiane;}
            void setPhiras(size_t phiras) { _phiras = phiras; }
            void setThystame(size_t thystame) { _thystame = thystame; }
            void setPlayers(size_t players) { _players = players; }
            void setEggs(size_t eggs) { _eggs = eggs; }
        private:
            size_t _food = 0;
            size_t _linemate = 0;
            size_t _deraumere = 0;
            size_t _sibur = 0;
            size_t _mendiane = 0;
            size_t _phiras = 0;
            size_t _thystame = 0;
            size_t _players = 0;
            size_t _eggs = 0;
    };
}
