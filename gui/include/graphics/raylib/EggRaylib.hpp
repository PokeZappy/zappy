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
            size_t gridSize, raylib::Shader &shader);
        void draw(const raylib::Camera camera);
        void update(void);
        int getAnimationIndex(const std::vector<std::string> &names);
        const std::shared_ptr<Egg> worldEgg;
    private:
        raylib::Model &_model;
        std::vector<raylib::ModelAnimation> &_modelAnimations;
    };
} // namespace Zappy
