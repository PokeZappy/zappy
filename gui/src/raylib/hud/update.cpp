/*
** EPITECH PROJECT, 2023
** gui
** File description:
** update.cpp
*/

#include "HudMode.hpp"

namespace Zappy {

    void HudMode::updateChat(ClientSocket &socket) {
        int input = GetCharPressed();
        if (input != 0)
            _inputString += input;
        if (IsKeyPressed(KEY_ENTER)) {
            // if (_inputString == "/help" || _inputString == "HELP")
            //     return;
            _inputString += '\n';
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

    void HudMode::update(ClientSocket &socket) {
        if (_chat) {
            updateChat(socket);
            return;
        }
        if (IsKeyPressed(KEY_T))
            _chat = true;

        if (_selectedPlayer == nullptr) {
            return;
        }
        if (IsKeyPressed(KEY_ONE)) {
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
            socket.sendData("HACK_HEALTH " + std::to_string(_selectedPlayer->worldPlayer->getId()) + " 1260");
        }
        if (IsKeyPressed(KEY_FOUR)) {
            // kill
            socket.sendData("KILL " + std::to_string(_selectedPlayer->worldPlayer->getId()));
        }
    }
}
