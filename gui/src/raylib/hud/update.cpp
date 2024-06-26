/*
** EPITECH PROJECT, 2023
** gui
** File description:
** update.cpp
*/

#include "HudMode.hpp"

namespace Zappy {
    // static std::vector<std::string> getHelpCommands(void)
    // {
    //     std::vector<std::string> commands;
    //     commands.push_back("Admin Commands:");
    //     commands.push_back("Modifier la position:   HACK_POS id x y");
    //     commands.push_back("Modifier la direction:  HACK_DIR id [UP/RIGHT/DOWN/LEFT]");
    //     commands.push_back("Modifier le niveau:     HACK_LEVEL id level");
    //     commands.push_back("Donner une ressource:   HACK_GIVE id resource quantity");
    //     commands.push_back("Modifier la vie:        HACK_HEALTH id health");
    //     commands.push_back("Tuer un joueur:         KILL id");
    //     commands.push_back("Modifier la fréquence:  sst time");
    //     commands.push_back("Inventaire d'une case:  HACK_WHOLE_TILE x y food linemate deraumere sibur mendiane phiras thystame");
    //     commands.push_back("Ressource d'une case:   HACK_TILE ressource quantity x y");

    //     commands.push_back("Légende:");
    //     commands.push_back("id: int, x: int, y: int, level: int, resource: string (food, linemate, etc.), quantity: int, time: int");

    //     return commands;
    //     // commands.push_back("Modifier la taille:     HACK_SIZE x y");
    //     // commands.push_back("Afficher les oeufs:     EGG_LIST");
    //     // commands.push_back("Afficher les clients:   CLIENT_LIST");
    // }

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
