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
        int defaultOffsetX = 30;
        int defaultOffsetY = GUI_HEIGHT - 280;

        unsigned char alpha = 255;

        for (auto &command : shellCommands) {
            sf::Color textColor = sf::Color::White;
            if (command.getEntity() != nullptr) {
                _shellTextTeamColor.setFillColor(getTeamColor(command.getEntity()->getTeam().getType()));
                _shellTextTeamColor.setPosition(defaultOffsetX - 20, defaultOffsetY + 5);
                _window.draw(_shellTextTeamColor);
                textColor = getEntityColor(command.getEntity());
            }
            textColor.a = alpha;
            alpha -= 4;
            _shellText.setColor(textColor);
            _shellText.setString(command.text);
            _shellText.setPosition(defaultOffsetX, defaultOffsetY);
            defaultOffsetY -= 20;
            _window.draw(_shellText);
        }
    }
} // namespace Zappy
