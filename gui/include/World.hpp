/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** World.hpp
*/

#pragma once

#include "Tile.hpp"
#include "Player.hpp"

namespace Zappy {
    class World {
    public:
        World() = default;
        ~World() = default;
        void initTiles(size_t width, size_t height);
        void updateTile(size_t x, size_t y, const Tile &tile);
        void updateTileInventory(size_t x, size_t y, const Inventory &inventory);

        void handleCommands(std::string &line);
        const std::vector<std::vector<Tile>> &getTiles() const { return (_tiles); }
        void addTeam(const std::string &teamName);
        // void addPlayer(std::unique_ptr<Player> &player) { _players.push_back(std::move(player)); }

        std::unique_ptr<Player> & getPlayer(size_t id);
    private:
        int _mapX = -1;
        int _mapY = -1;
        std::vector<std::vector<Tile>> _tiles;
        std::vector<std::string> _teams;
    };
} // namespace Zappy
