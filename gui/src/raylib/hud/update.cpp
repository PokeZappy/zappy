/*
** EPITECH PROJECT, 2023
** gui
** File description:
** update.cpp
*/

#include "HudMode.hpp"

namespace Zappy {

    void HudMode::updateChat(ClientSocket &socket, std::vector<std::shared_ptr<PlayerRaylib>> &players) {
        int input = GetCharPressed();
        if (input != 0)
            _inputString += input;
        if (IsKeyPressed(KEY_ENTER)) {
            _inputString += '\n';
            // aucune commande built in trouvée en cas de return false
            if (!execBuiltInCommand(_inputString, players))
                socket.sendData(_inputString);
            _chat = false;
            _inputString = "";
        } else if (IsKeyPressed(KEY_ESCAPE)) {
            _chat = false;
            _inputString = "";
        } else if (IsKeyPressed(KEY_BACKSPACE) || IsKeyPressedRepeat(KEY_BACKSPACE)) {
            if (!_inputString.empty())
                _inputString.pop_back();
        }
    }

    void HudMode::update(ClientSocket &socket, std::vector<std::shared_ptr<PlayerRaylib>> &players) {
        if (_chat) {
            updateChat(socket, players);
            return;
        }
        if (IsKeyPressed(KEY_T))
            _chat = true;

        if (_selectedPlayer == nullptr) {
            return;
        }
        if (IsKeyPressed(KEY_ONE)) {
            socket.sendData("HACK_LEVEL " + std::to_string(_selectedPlayer->worldPlayer->getId()) + " " + std::to_string(_selectedPlayer->worldPlayer->getLevel() + 1) + "\n");
            // ?,  surement level up
        }
        if (IsKeyPressed(KEY_TWO)) {
            // follow
            if (_targetedPlayer == _selectedPlayer)
                _targetedPlayer = nullptr;
            else
                _targetedPlayer = _selectedPlayer;
        }
        if (IsKeyPressed(KEY_THREE)) {
            // heal
            socket.sendData("HACK_HEALTH " + std::to_string(_selectedPlayer->worldPlayer->getId()) + " 1260\n");
        }
        if (IsKeyPressed(KEY_FOUR)) {
            // kill
            socket.sendData("KILL " + std::to_string(_selectedPlayer->worldPlayer->getId()) + "\n");
        }
    }
}
