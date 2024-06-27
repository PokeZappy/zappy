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
            StringButton(raylib::Rectangle dest, void (*onPressed)(Raylib &), std::string label = "", int fontSize = 10, bool state = false) : AButton(dest, onPressed, label), _fontSize(fontSize), _state(state) {};
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
            int _fontSize;
            bool _state = false;
            raylib::Color falseColor = raylib::Color::Red();
            raylib::Color trueColor = raylib::Color::Green();

    };
}