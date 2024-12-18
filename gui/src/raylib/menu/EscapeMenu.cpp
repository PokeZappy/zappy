/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** EscapeMenu.cpp
*/

#include "EscapeMenu.hpp"
#include "Raylib.hpp"

namespace Zappy {

    EscapeMenu::EscapeMenu(const std::string &assetsRoot, Raylib &core) :
            _backgroundHudTexture(assetsRoot + BASEWINDOW_HUD_PATH),
            _inventoryHudTexture(assetsRoot + INVENTORY_HUD_PATH) {


                int textSize = 60;
                int startY = 480;

                _minOptionsWidth = MeasureText("Options", textSize);

                _buttons.push_back(std::make_unique<TextureButton>(raylib::Rectangle(730, 206, 405, 115), assetsRoot + ATTACK_HUD_PATH, [](Raylib &raylib) {
                    raylib.getMenu()->switchState();
                }, "Continuer"));
                _buttons.push_back(std::make_unique<TextureButton>(raylib::Rectangle(730, 362, 405, 115), assetsRoot + ATTACK_HUD_PATH, [](Raylib &raylib) {
                    (void)raylib;
                    raylib.getMenu()->switchState();
                    raylib.getDebug()->activate(raylib.getCamera());
                }, "Debug"));
                _buttons.push_back(std::make_unique<TextureButton>(raylib::Rectangle(730, 512, 405, 115), assetsRoot + ATTACK_HUD_PATH, [](Raylib &raylib) {
                    (void)raylib;

                }, "Options"));
                _buttons.push_back(std::make_unique<TextureButton>(raylib::Rectangle(730, 662, 405, 115), assetsRoot + ATTACK_HUD_PATH, [](Raylib &raylib) {
                    raylib.getWindow().Close();
                }, "Quitter"));

                _buttons.push_back(std::make_unique<StringButton>(raylib::Rectangle(GUI_WIDTH - MeasureText("Show Players", textSize) - _rightMargin, startY, MeasureText("Show players", textSize), textSize), [](Raylib &raylib) {
                    raylib.setShowPlayers(!raylib.getShowPlayers());
                }, "Show players", textSize, core.getShowPlayers()));
                _minOptionsWidth = MeasureText("Show players", textSize) > _minOptionsWidth ? MeasureText("Show players", textSize) : _minOptionsWidth;

                _buttons.push_back(std::make_unique<StringButton>(raylib::Rectangle(GUI_WIDTH - MeasureText("Show eggs", textSize) - _rightMargin, startY + textSize + 15, MeasureText("Show eggs", textSize), textSize), [](Raylib &raylib) {
                    raylib.setShowEggs(!raylib.getShowEggs());
                }, "Show eggs", textSize, core.getShowEggs()));
                _minOptionsWidth = MeasureText("Show eggs", textSize) > _minOptionsWidth ? MeasureText("Show eggs", textSize) : _minOptionsWidth;

                _buttons.push_back(std::make_unique<StringButton>(raylib::Rectangle(GUI_WIDTH - MeasureText("Tint Players", textSize) - _rightMargin, startY + textSize * 2 + 15 * 2, MeasureText("Show players", textSize), textSize), [](Raylib &raylib) {
                    raylib.setTintPlayers(!raylib.getTintPlayers());
                }, "Tint players", textSize, core.getTintPlayers()));
                _minOptionsWidth = MeasureText("Tint players", textSize) > _minOptionsWidth ? MeasureText("Show players", textSize) : _minOptionsWidth;

                _buttons.push_back(std::make_unique<StringButton>(raylib::Rectangle(GUI_WIDTH - MeasureText("Music", textSize) - _rightMargin, startY + textSize * 3 + 15 * 3, MeasureText("Music", textSize), textSize), [](Raylib &raylib) {
                    raylib.setMusicState(!raylib.getMusicState());
                }, "Music", textSize, core.getMusicState()));
                _minOptionsWidth = MeasureText("Music", textSize) > _minOptionsWidth ? MeasureText("Music", textSize) : _minOptionsWidth;
    }

    void EscapeMenu::update(Raylib &core) {
        for (auto &button : _buttons) {
            button->hover();
            if (button->isPressed()) {
                button->press(core);
                break;
            }
        }
    }
}
