/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** AButton.hpp
*/

#pragma once

#include "IButton.hpp"
#include "raylib-cpp.hpp"

namespace Zappy {
    class AButton : public IButton {
        public:
            AButton(raylib::Rectangle dest, void (*onPressed)(Raylib &), std::string label = "") : _dest(dest), _onPressed(onPressed), _label(label) {}
            void hover() override {
                if (CheckCollisionPointRec(GetMousePosition(), _dest) && !IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
                    color = raylib::Color::Yellow();
                else
                    color = raylib::Color::White();
            }
            bool isPressed() override { return CheckCollisionPointRec(GetMousePosition(), _dest) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT); }

        protected:
            raylib::Rectangle _dest;
            void (*_onPressed)(Raylib &);
            raylib::Color color = raylib::Color::White();
            std::string _label;
    };
}