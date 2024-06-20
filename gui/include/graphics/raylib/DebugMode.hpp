/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** DebugMode.hpp
*/

#pragma once

#include "raylib-cpp.hpp"

namespace Zappy {
    class DebugMode {
    public:
        DebugMode(void) : _model(raylib::Model("assets/models/pokemons/ditto.glb")) {};
        // DebugMode(void) = default;
        void activate(void) {};
        void desactive(void) {};
        void changeAnimation(std::string newAnimation) {};
        void changeModel(std::string idModel) {};
        void changeScale(double newScale) {};
        void changeTexture(bool shiny = false) {};
        bool activated(void) { return _activated; };
    private:
        raylib::Model _model;
        double _scaleModel = 20.0f;
        bool _activated = false;    
        std::string _animationName = "ground_idle";
    };
}