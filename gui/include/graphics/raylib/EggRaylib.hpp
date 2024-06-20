/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** EggRaylib.hpp
*/

#include "Utils.hpp"
#include "Egg.hpp"
#include "AEntityRaylib.hpp"


namespace Zappy {
    class EggRaylib : public AEntityRaylib {
    public:
        EggRaylib(const std::shared_ptr<Egg> &worldEgg, bool shiny, size_t gridSize);
        void draw(const raylib::Camera camera);
        void update(void);
        void loadTextureAndModel(void);
        const std::shared_ptr<Egg> worldEgg;
        bool shiny = false;
    };
} // namespace Zappy