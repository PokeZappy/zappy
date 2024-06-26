/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** Player.hpp
*/

#pragma once

#include "Inventory.hpp"
#include "AEntity.hpp"
#include <memory>
#include "Utils.hpp"
#include <vector>
#include <sstream>


namespace Zappy {
    class Team;

    enum class Incantation {
        NONE,
        INCANTING,
        SUCCESS,
        FAILURE
    };

    class Player : public AEntity {
        public:
        Player(size_t id, size_t _posX, size_t _posY, Orientation orientation,
        size_t level, const Team &team) :
            AEntity(id, _posX, _posY, team), _orientation(orientation),
            _level(level), _incantingState(Incantation::NONE) {
        }
        ~Player() = default;

        EntityType getType(void) const override { return EntityType::PLAYER; }

        void setOrientation(Orientation orientation) {
            if (orientation != Orientation::NONE)
                _orientation = orientation;
        }
        void setLevel(size_t level) { _level = level; }
        void setIncanting(Incantation incantationState) { _incantingState = incantationState; }
        void setInventory(const Inventory &inventory) { _inventory = inventory; }
        void setBroadcast(const std::string &broadcast) { _broadcast = broadcast; }
        void setPush(bool push) { _push = push; }

        Orientation getOrientation() const { return _orientation; }
        size_t getLevel() const { return _level; }
        Incantation getIncantationState() const { return _incantingState; }
        Inventory &getInventory() { return _inventory; }
        const std::string &getBroadcast() const { return _broadcast; }
        bool isPushing() const { return _push; }
    private:
        Orientation _orientation;
        size_t _level;
        Incantation _incantingState;
        Inventory _inventory;
        std::string _broadcast;
        bool _push = false;
    };
} // namespace Zappy
