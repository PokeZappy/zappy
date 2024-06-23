/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** update.cpp
*/

#include "DebugMode.hpp"

namespace Zappy {

    void DebugMode::update() {
        switch (_type) {
            case NONE: updateNone(); break;
            case FRAMESTEPPER: updateFrameStepper(); break;
            case CHAT: updateChat(); break;
            default: break;
        }
    }

    void DebugMode::updateNone() {
        for (int i = 0; i < 9; i++) {
            if (IsKeyPressed(KEY_ONE + i)) {
                changeAnimationIndex(i);
            }
        }
        if (IsKeyPressed(KEY_ZERO)) {
            switchShiny();
        } else if (IsKeyPressed(KEY_I)) {
            changeAnimation(false);
        } else if (IsKeyPressed(KEY_K)) {
            changeAnimation(true);
        } else if (IsKeyPressed(KEY_J)) {
            lastModel();
        } else if (IsKeyPressed(KEY_L)) {
            nextModel();
        } else if (IsKeyPressed(KEY_F)) {
            _type = FRAMESTEPPER;
            _animFrame = 0;
        } else if (IsKeyPressed(KEY_T)) {
            _type = CHAT;
        }
    }

    void DebugMode::updateFrameStepper() {
        for (int i = 0; i < 9; i++) {
            if (IsKeyPressed(KEY_ONE + i)) {
                changeAnimationIndex(i);
            }
        }
        if (IsKeyPressed(KEY_ZERO)) {
            switchShiny();
        } else if (IsKeyPressed(KEY_F)) {
            _type = NONE;
            _animFrame = 0;
        } else if (IsKeyDown(KEY_J)) {
            _animFrame--;
            if (_animFrame < 0)
                _animFrame = _animations[_animIndex].frameCount;
        } else if (IsKeyDown(KEY_L)) {
            _animFrame++;
            if (_animFrame > _animations[_animIndex].frameCount)
                _animFrame = 0;
        } else if (IsKeyPressed(KEY_I)) {
            changeAnimation(false);
            _animFrame = 0;
        } else if (IsKeyPressed(KEY_K)) {
            changeAnimation(true);
            _animFrame = 0;
        }
    }

    void DebugMode::updateChat() {
        int input = GetCharPressed();
        if (input != 0)
            _pokemonInput += input;
        if (IsKeyPressed(KEY_ENTER)) {
            changeModel(_pokemonInput);
            _type = NONE;
            _pokemonInput = "";
        } else if (IsKeyPressed(KEY_BACKSPACE) || IsKeyPressedRepeat(KEY_BACKSPACE)) {
            if (!_pokemonInput.empty())
                _pokemonInput.pop_back();
        }
    }
}
