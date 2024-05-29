/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** drawShell.cpp
*/

#include "Sfml.hpp"
#include "ShellCommand.hpp"

namespace Zappy
{
    void Sfml::drawShell(const std::vector<ShellCommand> &shellCommands)
    {
        int defaultWidth = 900;
        int defaultHeight = GUI_HEIGHT - 280;

        unsigned char alpha = 255;

        for (auto &command : shellCommands) {
            sf::Color textColor = sf::Color::White;
            if (command.getPlayer() != nullptr) {
                _shellTextTeamColor.setFillColor(getTeamColor(command.getPlayer()->getTeam().getType()));
                _shellTextTeamColor.setPosition(defaultWidth - 20, defaultHeight + 5);
                _window.draw(_shellTextTeamColor);
                textColor = getPlayerColor(command.getPlayer());
            }
            textColor.a = alpha;
            alpha -= 4;
            _shellText.setColor(textColor);
            _shellText.setString(command.text);
            _shellText.setPosition(defaultWidth, defaultHeight);
            defaultHeight -= 20;
            _window.draw(_shellText);
        }
    }
} // namespace Zappy
