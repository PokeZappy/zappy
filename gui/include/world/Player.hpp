/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** Player.hpp
*/

#pragma once

#include "Inventory.hpp"
#include "Tools.hpp"

#include <sstream>

namespace Zappy {
    class Player {
    public:
        Player(std::istringstream &ss) {
            size_t newOrientation;
            ss >> _id >> _posX >> _posY >> newOrientation >> _level >> _teamName;
            if (newOrientation > 0 && newOrientation < 5)
                _orientation = static_cast<Orientation>(newOrientation);
        }
        Player() {
            _id = 0;
            _posX = 0;
            _posY = 0;
            _orientation = Orientation::EAST;
            _level = 1;
            _isIncanting = false;

        }
        Player(size_t id, size_t _posX, size_t _posY, Orientation orientation,
        size_t level, bool isIncanting) :
            _id(id), _posX(_posX), _posY(_posY), _orientation(orientation),
            _level(level), _isIncanting(isIncanting) {

        }
        ~Player() = default;

        void setId(size_t id) { _id = id; }
        void setPos(size_t x, size_t y, Orientation orientation = Orientation::NONE) {
            _posX = x;
            _posY = y;
            if (orientation != Orientation::NONE)
                _orientation = orientation;
        }
        void setLevel(size_t level) { _level = level; }
        void setTeamName(const std::string &teamName) { _teamName = teamName; }
        void setIncanting(bool isIncanting) { _isIncanting = isIncanting; }
        void setInventory(const Inventory &inventory) { _inventory = inventory; }

        size_t getId() const { return _id; }
        size_t getPosX() const { return _posX; }
        size_t getPosY() const { return _posY; }
        Orientation getOrientation() const { return _orientation; }
        size_t getLevel() const { return _level; }
        std::string getTeamName() const { return _teamName; }
        bool isIncanting() const { return _isIncanting; }
        Inventory &getInventory() { return _inventory; }

    private:
        size_t _id;
        size_t _posX;
        size_t _posY;
        Orientation _orientation;
        size_t _level;
        std::string _teamName;
        bool _isIncanting;
        Inventory _inventory;
    };
} // namespace Zappy
