/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** Player.hpp
*/

#pragma once

#include "Inventory.hpp"
#include "Tools.hpp"
#include "AEntity.hpp"
#include <memory>
#include <vector>
#include <sstream>


namespace Zappy {
    class Team;

    class Player : public AEntity {
        public:
        // Player(std::istringstream &ss) {
        //     size_t newOrientation;
        //     std::string teamName;
        //     ss >> _id >> _posX >> _posY >> newOrientation >> _level >> teamName;
        //     if (newOrientation > 0 && newOrientation < 5)
        //         _orientation = static_cast<Orientation>(newOrientation);
        // }
        Player(size_t id, size_t _posX, size_t _posY, Orientation orientation,
        size_t level, Team &team) :
            AEntity(id, _posX, _posY, team), _orientation(orientation),
            _level(level), _isIncanting(false) {

        }
        ~Player() = default;

        void setPos(size_t x, size_t y, Orientation orientation = Orientation::NONE) {
            _x = x;
            _y = y;
            if (orientation != Orientation::NONE)
                _orientation = orientation;
        }
        void setLevel(size_t level) { _level = level; }
        void setIncanting(bool isIncanting) { _isIncanting = isIncanting; }
        void setInventory(const Inventory &inventory) { _inventory = inventory; }

        Orientation getOrientation() const { return _orientation; }
        size_t getLevel() const { return _level; }
        bool isIncanting() const { return _isIncanting; }
        Inventory &getInventory() { return _inventory; }
    private:
        Orientation _orientation;
        size_t _level;
        bool _isIncanting;
        Inventory _inventory;
    };
} // namespace Zappy
