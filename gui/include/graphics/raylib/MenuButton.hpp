/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** MenuButton.hpp
*/

#pragma once

#include "raylib-cpp.hpp"
#include <functional>
#include "Raylib.hpp"

namespace Zappy {

    class EscapeMenu;
    class Raylib;

    class MenuButton {

        public:
            MenuButton(raylib::Rectangle dest, std::string texturePath, void (*onPressed)(Raylib &), std::string label = "") : _dest(dest), _texture(texturePath), _onPressed(onPressed), _label(label) {
                _src = raylib::Rectangle(0, 0, _texture.width, _texture.height);
            };
            MenuButton(raylib::Rectangle src, raylib::Rectangle dest, std::string texturePath, void (*onPressed)(Raylib &), std::string label = "") : _src(src), _dest(dest), _texture(texturePath), _onPressed(onPressed), _label(label) { };
            void draw() { 
                _texture.Draw(_src, _dest);
                int width = MeasureText(_label.c_str(), 25);
                color.DrawText(_label, _dest.x + _dest.width / 2 - width / 2, _dest.y + _dest.height / 2 - 10, 25);
                };
            void press(Raylib &raylib) { _onPressed(raylib); }
            void hover(bool isHovered) {
                if (isHovered)
                    color = raylib::Color::Yellow();
                else
                    color = raylib::Color::White();
            }
            bool isPressed() { return CheckCollisionPointRec(GetMousePosition(), _dest) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT); }
            bool isHover() { return CheckCollisionPointRec(GetMousePosition(), _dest) && !IsMouseButtonPressed(MOUSE_BUTTON_LEFT); }
        private:
            raylib::Rectangle _src;
            raylib::Rectangle _dest;
            raylib::Texture2D _texture;
            void (*_onPressed)(Raylib &);
            bool _state = false;
            raylib::Color color = raylib::Color::White();
            std::string _label;
    };
}