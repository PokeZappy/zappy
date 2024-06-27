/*
** EPITECH PROJECT, 2023
** gui
** File description:
** drawMenu.cpp
*/

#include "Raylib.hpp"

namespace Zappy {
    void Raylib::drawMenu() {
        double blinkTime = 1.5;
        std::chrono::duration<double> elapsed_seconds = std::chrono::steady_clock::now() - _menuClock;
        if (elapsed_seconds.count() < blinkTime) {
            raylib::Color(0, 0, 0, (255 / blinkTime) * (elapsed_seconds.count())).DrawText("Appuyez sur ENTREE pour continuer . . .", 100, GUI_HEIGHT - 100, 45);
        } else if (elapsed_seconds.count() >= blinkTime && elapsed_seconds.count() <= blinkTime * 2) {
            raylib::Color(0, 0, 0, 255 - (255 / blinkTime) * (elapsed_seconds.count() - blinkTime)).DrawText("Appuyez sur ENTREE pour continuer . . .", 100, GUI_HEIGHT - 100, 45);
        } else
            _menuClock = std::chrono::steady_clock::now();
    }
}
