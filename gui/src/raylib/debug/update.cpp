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
            default: break;
        }
    }

    void DebugMode::updateNone() {
        if (IsKeyPressed(KEY_ONE)) {
                changeAnimation(0);
            } else if (IsKeyPressed(KEY_TWO)) {
                changeAnimation(1);
            } else if (IsKeyPressed(KEY_THREE)) {
                changeAnimation(2);
            } else if (IsKeyPressed(KEY_FOUR)) {
                changeAnimation(3);
            } else if (IsKeyPressed(KEY_FIVE)) {
                changeAnimation(4);
            } else if (IsKeyPressed(KEY_SIX)) {
                changeAnimation(5);
            } else if (IsKeyPressed(KEY_SEVEN)) {
                changeAnimation(6);
            } else if (IsKeyPressed(KEY_EIGHT)) {
                changeAnimation(7);
            } else if (IsKeyPressed(KEY_NINE)) {
                changeAnimation(8);
            }else if (IsKeyPressed(KEY_ZERO)) {
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
            }
    }

    void DebugMode::updateFrameStepper() {
        if (IsKeyPressed(KEY_F)) {
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
}