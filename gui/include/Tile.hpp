/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Tile.hpp
*/

#pragma once

#include "Inventory.hpp"
#include "world/Player.hpp"

namespace Zappy {
    class Tile {
        public:
            Tile() = default;
            Tile(size_t x, size_t y) : _x(x), _y(y) {}
            Tile(Inventory inventory, int x, int y) :
                _inventory(inventory), _x(x), _y(y) {}
            ~Tile() = default;

            void setInventory(const Inventory &inventory) { _inventory = inventory; }
            // void addPlayer(std::unique_ptr<Player> &player) { _players.push_back(std::move(player)); }

            const Inventory &getInventory() const { return _inventory; }
            size_t getItem(size_t index) const { return _inventory.getItem(index); }
            size_t getX() { return _x; }
            size_t getY() { return _y; }
            // const std::vector<std::unique_ptr<Player>> &getPlayers() const { return _players; }
            // std::vector<std::unique_ptr<Player>> &getPlayers() { return _players; }
        private:
            Inventory _inventory;
            size_t _x;
            size_t _y;
            // std::vector<Player *> _players;
            // std::vector<std::shared_ptr<Player>> _players;
            // std::vector<size_t> _playersId;

            // size_t _eggs = 0;
    };
}
