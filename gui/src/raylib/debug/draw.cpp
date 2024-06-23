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
    }

    void DebugMode::drawAnimations(void) {
        raylib::Color white = raylib::Color::White();
        raylib::Color green = raylib::Color::Green();

        raylib::Vector2 startPos(1400, 100);
        white.DrawText("Animations: (I, K)", startPos.x, startPos.y - 70, 60);
        for (size_t i = 0; i < _animations.size(); i++) {
            if ((int)i == _animIndex) {
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
        white.DrawText("Select Pokemon = T", 10, 750, 45);
        white.DrawText("FrameStepper = F", 10, 850, 45);
        white.DrawText("Shiny = NUM 0", 10, 950, 45);
        _animFrame++;
    }

    void DebugMode::drawFrameStepper(void) {
        raylib::Color white = raylib::Color::White();
        raylib::Color green = raylib::Color::Green();
        
        green.DrawText(_animations[_animIndex].name, 400, 20, 50);
        white.DrawText("Frame: " + std::to_string(_animFrame) + "/" + std::to_string(_animations[_animIndex].frameCount) + " (J, L pour changer de frame)", 550, 75, 30);

        white.DrawText("Appuyez sur F pour quitter le mode FrameStepper", 10, 950, 45);
    }

    void DebugMode::drawChat(void) {
        raylib::Color white = raylib::Color::White();
        raylib::Color black = raylib::Color::Black();

        white.DrawText("Appuyez sur ENTRÉE pour confirmer", 625, 825, 40);
        white.DrawRectangle((Vector2) {50, 880}, (Vector2) {1800, 120});
        black.DrawText(_pokemonInput.empty() ? "_" : _pokemonInput, 80, 940, 40);
    }
}
