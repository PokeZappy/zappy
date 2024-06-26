/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** EscapeMenu.cpp
*/

#include "EscapeMenu.hpp"
#include "Raylib.hpp"

namespace Zappy {

    EscapeMenu::EscapeMenu(const std::string &assetsRoot) :
            _backgroundHudTexture(assetsRoot + BASEWINDOW_HUD_PATH),
            _inventoryHudTexture(assetsRoot + INVENTORY_HUD_PATH) {
                _buttons.push_back(MenuButton(raylib::Rectangle(730, 206, 405, 115), assetsRoot + ATTACK_HUD_PATH, [](Raylib &raylib) {
                    raylib.getMenu()->switchState();
                }, "Resume"));
                _buttons.push_back(MenuButton(raylib::Rectangle(730, 362, 405, 115), assetsRoot + ATTACK_HUD_PATH, [](Raylib &raylib) {
                    (void)raylib;
                    raylib.getMenu()->switchState();
                    raylib.getDebug()->activate(raylib.getCamera());
                }, "Debug"));
                _buttons.push_back(MenuButton(raylib::Rectangle(730, 512, 405, 115), assetsRoot + ATTACK_HUD_PATH, [](Raylib &raylib) {
                    (void)raylib;
                    
                }, "Options"));
                _buttons.push_back(MenuButton(raylib::Rectangle(730, 662, 405, 115), assetsRoot + ATTACK_HUD_PATH, [](Raylib &raylib) {
                    raylib.getWindow().Close();
                }, "Quit"));
    }

    void EscapeMenu::update(Raylib &core) {
        for (auto &button : _buttons) {
            if (button.isHover()) {
                button.hover(true);
            } else {
                button.hover(false);
            }
            if (button.isPressed()) {
                button.press(core);
                break;
            }
        }
    }
}