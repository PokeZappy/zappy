/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** DebugMode.hpp
*/

#pragma once

#include "raylib-cpp.hpp"
#include "Utils.hpp"
#include <filesystem>
#include <algorithm>

namespace Zappy {
    enum DebugType {
        NONE = 0,
        FRAMESTEPPER,
        CHAT
    };

    class DebugMode {
    public:
        DebugMode(const std::string &assetsRoot, raylib::Shader &shader, float gridSize);
        void activate(raylib::Camera &camera);
        void desactive(raylib::Camera &camera);
        void changeAnimation(int index);
        void changeAnimation(bool increments);
        void changeModel(std::string idModel);
        void nextModel();
        void lastModel();
        void switchShiny() {
            _shiny = !_shiny;
            changeTexture();
        }
        void changeScale(double newScale) {};
        void changeTexture();
        void loadModel();
        bool activated(void) { return _activated; };
        const raylib::Model &getModel(void) const { return _model; }
        double getScale() { return _scaleModel; }
        DebugType getType(void) { return _type; }
        bool isShiny() { return _shiny; }
        int getAnimIndex() { return _animIndex; }
        void drawModel();
        void drawAnimations();
        void drawPokemon();
        void drawFrameStepper();
        void drawChat();
        void update();
        void updateNone();
        void updateFrameStepper();
        void updateChat();
    private:
        const std::string &_assetsRoot;
        float _gridSize;
        DebugType _type = NONE;
        std::string _pokemonInput = "";
        Texture2D _oldTexture;
        std::vector<std::string> _modelsId;
        int _modelIndex = 0;
        raylib::Model _model;
        std::vector<raylib::ModelAnimation> _animations;
        double _scaleModel = 1.f;
        bool _activated = false;
        bool _shiny = false;
        int _animIndex = -1;
        int _animFrame = 0;
        raylib::Shader &_shader;
    };
}
