/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** AEntity.hpp
*/

#pragma once

#include "IEntity.hpp"

namespace Zappy {
    class AEntity : public IEntity {
        public:
            AEntity(size_t id, size_t x, size_t y, const Team &team);
            size_t getId() override { return (_id); }
            size_t getX() override { return (_x); }
            size_t getY() override { return (_y); }
            void setId(size_t id) override { _id = id; }
            void setPos(size_t x, size_t y) override { _x = x; _y = y; }
            const Team &getTeam() const override { return (_team); };
        protected:
            size_t _id;
            size_t _x;
            size_t _y;
            const Team &_team;
    };
}
