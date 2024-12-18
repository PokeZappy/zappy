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
        EggRaylib(const std::shared_ptr<Egg> &worldEgg, raylib::Model &model,
            std::vector<raylib::ModelAnimation> &animations,
            float gridSize, raylib::Shader &shader, raylib::Color tint);
        void draw(void);

        void update(void);
        int getAnimationIndex(const std::vector<std::string> &names);
        const std::shared_ptr<Egg> worldEgg;
    private:
        raylib::Model &_model;
        raylib::Color _tint;
        std::vector<raylib::ModelAnimation> &_modelAnimations;
        std::unordered_map<std::string, int> _animationIndexes;
    };
} // namespace Zappy
