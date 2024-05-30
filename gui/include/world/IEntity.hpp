/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** IEntity.hpp
*/

#pragma once
#include <iostream>
#include "Team.hpp"

namespace Zappy {
    enum class EntityType {
        PLAYER,
        EGG,
        SIZE
    };
    class IEntity {
        public:
            virtual ~IEntity() = default;
            virtual size_t getId() = 0;
            virtual size_t getX() = 0;
            virtual size_t getY() = 0;
            virtual void setId(size_t id) = 0;
            virtual void setPos(size_t x, size_t y) = 0;
            virtual EntityType getType(void) const = 0;
            virtual const Team &getTeam() const = 0;
    };
}
