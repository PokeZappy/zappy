/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** Egg.hpp
*/

#pragma once

#include "Inventory.hpp"
#include "Tools.hpp"
#include "world/Team.hpp"
#include "AEntity.hpp"
#include <memory>
#include <vector>
#include <sstream>

namespace Zappy {
    class Egg : public AEntity {
        public:
            Egg(size_t id, int idPlayer, size_t _posX, size_t _posY, const Team &team) :
                AEntity(id, _posX, _posY, team), _idPlayer(idPlayer) {
            }
            ~Egg() = default;

            EntityType getType(void)const override { return EntityType::EGG; }

            int getIdPlayer() { return (_idPlayer); }
        private:
            int _idPlayer;
    };
}
