/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** RaylibModels.hpp
*/

#pragma once

#include <unordered_map>
#include "RaylibModel.hpp"
#include <memory>

namespace Zappy {

    namespace Animations {
        enum Type {
        IDLE,
        WALK,
        SLEEP,
        CRY,
        NONE
        };
    }

    class RaylibModels {
    public:
        RaylibModels(const std::string &assetsRoot, std::string id, raylib::Shader &shader) {
            std::string shinyPath = assetsRoot + "textures/pokemons/" + id + "_shiny.png";
            _shinyTexture = LoadTexture(shinyPath.c_str());

            _animations = raylib::ModelAnimation::Load(assetsRoot + "models/pokemons/" + id + ".glb");

            int indexIdle = getAnimationIndex({"ground_idle"});
            int indexWalk = getAnimationIndex({"ground_run", "ground_walk"});
            int indexSleep = getAnimationIndex({"sleep"});
            int indexCry = getAnimationIndex({"cry"});
            if (indexIdle != -1) {
                _models[Animations::IDLE] = std::make_shared<RaylibModel>(assetsRoot, id, shader, indexIdle);
            }
            if (indexWalk != -1) {
                _models[Animations::WALK] = std::make_shared<RaylibModel>(assetsRoot, id, shader, indexWalk);
            }
            if (indexSleep != -1) {
                _models[Animations::SLEEP] = std::make_shared<RaylibModel>(assetsRoot, id, shader, indexSleep);
            }
            if (indexCry != -1) {
                _models[Animations::CRY] = std::make_shared<RaylibModel>(assetsRoot, id, shader, indexCry);
            }
            _models[Animations::NONE] = std::make_shared<RaylibModel>(assetsRoot, id, shader, -1);
            
            _normalTexture = _models[Animations::NONE]->getTexture();
        }
        void update();
        bool hasAnim(Animations::Type anim);
        void setShinyTexture(Animations::Type anim) { _models[anim]->setShinyTexture(_shinyTexture); };
        void updateAnimation(Animations::Type anim) { _models[anim]->updateAnimation(_animations); };
        std::shared_ptr<RaylibModel> getModelByAnimation(Animations::Type anim) { return _models[anim]; }
        void setNormalTexture(Animations::Type anim) { _models[anim]->setNormalTexture(_normalTexture); };

        int getAnimationIndex(const std::vector<std::string> &names)
        {
            for (size_t i = 0; i < _animations.size(); i++) {
                std::string animName(_animations[i].name);
                for (size_t j = 0; j < names.size(); j++) {
                    if (animName.find(names[j]) != std::string::npos) {
                        return i;
                    }
                }
            }
            return -1;
        }

    private:
        Texture2D _normalTexture;
        Texture2D _shinyTexture;
        std::vector<raylib::ModelAnimation> _animations;
        std::unordered_map<Animations::Type, std::shared_ptr<RaylibModel>> _models;
    };
}
