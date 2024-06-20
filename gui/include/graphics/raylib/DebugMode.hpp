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
    };

    class DebugMode {
    public:
        DebugMode(void);
        // DebugMode(void) = default;
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
        void update();
        void updateNone();
        void updateFrameStepper();
    private:
        DebugType _type = NONE;
        Texture2D _oldTexture;
        std::vector<std::string> _modelsId;
        int _modelIndex = 0;
        raylib::Model _model;
        std::vector<raylib::ModelAnimation> _animations;
        double _scaleModel = 20.0f;
        bool _activated = false;    
        bool _shiny = false;
        int _animIndex = -1;
        int _animFrame = 0;
    };
}