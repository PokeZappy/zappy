/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** World.hpp
*/

#pragma once

#include "Tile.hpp"
#include "world/Player.hpp"
#include "Egg.hpp"
#include "world/Team.hpp"
#include "ShellCommand.hpp"
#include "Utils.hpp"
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
        void addEgg(std::shared_ptr<Egg> egg) { _eggs.push_back(egg); }
        std::shared_ptr<Egg> getEgg(size_t id);
        std::shared_ptr<Player> getPlayer(size_t id);
        const std::vector<std::shared_ptr<Player>> &getPlayers() const { return _players; }
        std::vector<std::shared_ptr<Player>> getPlayers(size_t x, size_t y);
        const std::vector<std::shared_ptr<Egg>> &getEggs() const { return _eggs; }
        void killPlayer(size_t id);
        void killEgg(size_t id);

        void addTeam(const std::string &teamName);
        Team &getTeam(const std::string &teamName);

        const std::vector<ShellCommand> &getShellCommands(void) const;
        void addShellCommand(const std::string &text, std::shared_ptr<IEntity> entity = nullptr);
        bool containsPlayer(size_t id) const;
        bool containsEgg(size_t id) const;
        int _mapX = -1;
        int _mapY = -1;
    private:
        std::string getOrientationString(Orientation orientation);
        std::string getItemString(Item item);
        std::vector<std::vector<Tile>> _tiles;
        std::vector<Team> _teams;
        Team defaultTeam;
        // todo: vector of IEntity ?
        std::vector<std::shared_ptr<Player>> _players;
        std::vector<std::shared_ptr<Egg>> _eggs;
        std::vector<ShellCommand> _shellCommands;
        size_t _shellOffset = 0;
    };
} // namespace Zappy
