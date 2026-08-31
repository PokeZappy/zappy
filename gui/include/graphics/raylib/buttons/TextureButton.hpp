/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** MenuButton.hpp
*/

#pragma once

#include <functional>
#include "Raylib.hpp"
#include "AButton.hpp"

namespace Zappy {

    class EscapeMenu;
    class Raylib;

    class TextureButton : public AButton {

        public:
            TextureButton(raylib::Rectangle dest, std::string texturePath, void (*onPressed)(Raylib &), std::string label = "") : AButton(dest, onPressed, label), _texture(texturePath) {
                _src = raylib::Rectangle(0, 0, _texture.width, _texture.height);
            };
            TextureButton(raylib::Rectangle src, raylib::Rectangle dest, std::string texturePath, void (*onPressed)(Raylib &), std::string label = "") : AButton(dest, onPressed, label), _src(src), _texture(texturePath) { };
            void draw() override {
                raylib::Rectangle dest = rect();
                int fontSize = Layout::s(25);
                _texture.Draw(_src, dest);
                int width = MeasureText(_label.c_str(), fontSize);
                color.DrawText(_label, dest.x + dest.width / 2 - width / 2,
                    dest.y + dest.height / 2 - Layout::s(10), fontSize);
                };
            void press(Raylib &raylib) override {
                _onPressed(raylib); }
        private:
            raylib::Rectangle _src;
            raylib::Texture2D _texture;
    };
}