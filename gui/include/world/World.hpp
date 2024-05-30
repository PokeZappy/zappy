/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** World.hpp
*/

#pragma once

#include "Tile.hpp"
#include "world/Player.hpp"
#include "world/Team.hpp"
#include "ShellCommand.hpp"
#include <algorithm>
#include <memory>
#include <algorithm>

namespace Zappy {
    class World {
    public:
        World() = default;
        ~World() = default;
        void initTiles(size_t width, size_t height);
        void updateTile(size_t x, size_t y, const Tile &tile);
        void updateTileInventory(size_t x, size_t y, const Inventory &inventory);

        void handleCommand(std::string &command);
        const std::vector<std::vector<Tile>> &getTiles() const { return (_tiles); }
        TeamType determineTeamType(const std::string &teamName);

        void addPlayer(std::shared_ptr<Player> player) { _players.push_back(player); }
        std::shared_ptr<Player> getPlayer(size_t id);
        const std::vector<std::shared_ptr<Player>> &getPlayers() const { return _players; }
        std::vector<std::shared_ptr<Player>> getPlayers(size_t x, size_t y);
        void killPlayer(size_t id);

        void addTeam(const std::string &teamName);
        Team &getTeam(const std::string &teamName);

        const std::vector<ShellCommand> &getShellCommands(void) const;
        void addShellCommand(const std::string &text, std::shared_ptr<Player> player = nullptr);
    private:
        int _mapX = -1;
        int _mapY = -1;
        std::vector<std::vector<Tile>> _tiles;
        std::vector<Team> _teams;
        std::vector<std::shared_ptr<Player>> _players;
        std::vector<ShellCommand> _shellCommands;
        size_t _shellOffset = 0;
    };
} // namespace Zappy
