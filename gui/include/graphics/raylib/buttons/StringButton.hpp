/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** StringButton.hpp
*/

#pragma once

#include "AButton.hpp"

namespace Zappy {

    class Raylib;

    class StringButton : public AButton {
        public:
            StringButton(raylib::Rectangle dest, void (*onPressed)(Raylib &), std::string label = "", int fontSize = 10) : AButton(dest, onPressed, label), _fontSize(fontSize) {};
            void draw() override {
                if (_state)
                    trueColor.DrawText(_label, _dest.x, _dest.y, _fontSize);
                else
                    falseColor.DrawText(_label, _dest.x, _dest.y, _fontSize);
            }
            void press(Raylib &core) override {
                _state = !_state;
                _onPressed(core);
            }
            void hover() override {}
        private:
            bool _state = false;
            int _fontSize;
            raylib::Color falseColor = raylib::Color::Red();
            raylib::Color trueColor = raylib::Color::Green();

    };
}