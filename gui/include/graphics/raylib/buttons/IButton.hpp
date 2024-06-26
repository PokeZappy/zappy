/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** IButton.hpp
*/

namespace Zappy {

    class Raylib;

    class IButton {
        public:
            virtual ~IButton() = default;
            virtual void press(Raylib &raylib) = 0;
            virtual void hover() = 0;
            virtual bool isPressed() = 0;
            virtual void draw() = 0;
    };
}