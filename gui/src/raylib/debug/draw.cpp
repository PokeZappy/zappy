/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** draw.cpp
*/

#include "DebugMode.hpp"

namespace Zappy {
    void DebugMode::drawModel(void) {
        if (_animIndex != -1)
                _model.UpdateAnimation(_animations[_animIndex], _animFrame);
            _model.Draw((Vector3) {0, 0, 0},
            raylib::Vector3(0, 1, 0), 0,
            raylib::Vector3(_scaleModel, _scaleModel, _scaleModel));
            _animFrame++;   
    }

    void DebugMode::drawAnimations(void) {
        raylib::Color white = raylib::Color::White();
        raylib::Color green = raylib::Color::Green();
    
        raylib::Vector2 startPos(1400, 100);
        white.DrawText("Animations: (I, K)", startPos.x, startPos.y - 70, 60);
        for (size_t i = 0; i < _animations.size(); i++) {
            if (i == _animIndex) {
                green.DrawText("- " + std::string(_animations[i].name), startPos.x, startPos.y, 30);
            } else {
                white.DrawText(std::string(_animations[i].name), startPos.x, startPos.y, 30);
            }
            startPos.y += 50;
        }
    }

    void DebugMode::drawPokemon(void) {
        raylib::Color white = raylib::Color::White();

        white.DrawText("Pokemon séléctionné : (J, L)", 50, 50, 60);
        white.DrawText(_modelsId[_modelIndex], 230, 120, 45);
        white.DrawText("Shiny = touche 0", 10, 950, 45);
    }
}