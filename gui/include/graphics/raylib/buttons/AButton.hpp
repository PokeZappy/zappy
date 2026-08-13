/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** AButton.hpp
*/

#pragma once

#include "IButton.hpp"
#include "raylib-cpp.hpp"
#include "Layout.hpp"

namespace Zappy {
    class AButton : public IButton {
        public:
            // Which screen edge the design-space X is measured from.
            enum class Anchor { Left, Right };

            AButton(raylib::Rectangle dest, void (*onPressed)(Raylib &),
                std::string label = "", Anchor anchor = Anchor::Left)
                : _dest(dest), _anchor(anchor), _onPressed(onPressed), _label(label) {}

            // Live screen-space rect. Drawing and hit-testing both go through this, so
            // they can never disagree, and it follows window resizes for free.
            raylib::Rectangle rect(void) const {
                float x = (_anchor == Anchor::Right) ? Layout::right(_dest.x)
                                                     : Layout::left(_dest.x);
                return raylib::Rectangle(x, Layout::top(_dest.y),
                    Layout::s(_dest.width), Layout::s(_dest.height));
            }

            void hover() override {
                if (CheckCollisionPointRec(GetMousePosition(), rect()) && !IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
                    color = raylib::Color::Yellow();
                else
                    color = raylib::Color::White();
            }
            bool isPressed() override { return CheckCollisionPointRec(GetMousePosition(), rect()) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT); }

        protected:
            raylib::Rectangle _dest;   // design space, converted by rect()
            Anchor _anchor;
            void (*_onPressed)(Raylib &);
            raylib::Color color = raylib::Color::White();
            std::string _label;
    };
}