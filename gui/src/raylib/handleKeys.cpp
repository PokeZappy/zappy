/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** update.cpp
*/

#include "Raylib.hpp"

namespace Zappy {
    void Raylib::handleKeys(void)
    {
        float moveYSpeed = _gridSize / 15.;
        if (debugMode->getType() != CHAT && (!_hudMode->isChatEnabled())) {
             if (IsKeyDown(KEY_SPACE)) {
            _camera.position.y += moveYSpeed;
            _camera.target.y += moveYSpeed;
            }
            if (IsKeyDown(KEY_LEFT_SHIFT))
            {
                _camera.position.y -= moveYSpeed;
                _camera.target.y -= moveYSpeed;
            }

            if (IsKeyPressed(KEY_N)) {
            _hudMode->switchState();
            }

            if (IsKeyPressed(KEY_P)) {
                if (debugMode->activated()) {
                    debugMode->desactive(_camera, _defaultCameraPosition,
                        _defaultCameraTarget, _defaultAmbientLight);
                } else {
                    debugMode->activate(_camera);
                }
        }
        }

        if (debugMode->activated()) {
            debugMode->update();
        } else if (!_hudMode->activated()) {
            if (IsKeyPressed(KEY_ONE)) {
                _mapX++;
                _mapY++;
            } else if (IsKeyPressed(KEY_TWO)) {
                _mapX--;
                _mapY--;
            } else if (IsKeyPressed(KEY_THREE)) {
                _arena = raylib::Model(_assetsRoot + "local/boxing_ring.glb");
                for (int i = 0; i < _arena.materialCount; i++)
                    _arena.materials[i].shader = _shader;
                _arenaScale = _gridSize * 0.0265;
                _arenaAltitudeScale = _gridSize * 80;
                getArenaOffset = [](size_t tileCount, float gridSize) -> float {
                    (void)gridSize;
                    return - gridSize * 0.5 - (float)tileCount * 0.14 * gridSize;
                };
            } else if (IsKeyPressed(KEY_T)) {
                _mapX = 10;
                _mapY = 10;
            } else if (IsKeyPressed(KEY_Y)) {
                _mapX = 20;
                _mapY = 20;
            } else if (IsKeyPressed(KEY_U)) {
                _mapX = 30;
                _mapY = 30;
            }
        }

        if (debugMode->getType() != CHAT && (!_hudMode->isChatEnabled()))
            _camera.Update(_cameraViewMode);

        // if (!_players.empty() && !_players[0]->isDying()) {
            //* Follow the player with id 0
            // for (auto &player : _players) {
            //     if (_players[0]->worldPlayer->getId() == 0) {
            //         _camera.target = player->getPosition() * _gridSize;
            //         TraceLog(LOG_WARNING, "Camera target: %d", player->worldPlayer->getId());
            //         break;
            //     }
            // }
            //* Follow the first player
            // _camera.target = _players[0]->getPosition() * _gridSize;
            // _camera.position = _players[0]->getPosition() * _gridSize + Vector3{-50, 50, 100};
        // }

        // Update the shader with the camera view vector (points towards { 0.0f, 0.0f, 0.0f })
        float cameraPos[3] = { _camera.position.x, _camera.position.y, _camera.position.z };
        SetShaderValue(_shader, _shader.locs[SHADER_LOC_VECTOR_VIEW], cameraPos, SHADER_UNIFORM_VEC3);

        // Check key inputs to enable/disable lights
        if (IsKeyPressed(KEY_Y)) { _lights[0].enabled = !_lights[0].enabled; }
        if (IsKeyPressed(KEY_R)) { _lights[1].enabled = !_lights[1].enabled; }
        if (IsKeyPressed(KEY_G)) { _lights[2].enabled = !_lights[2].enabled; }
        if (IsKeyPressed(KEY_B)) { _lights[3].enabled = !_lights[3].enabled; }

        if (IsKeyPressed(KEY_Y)) _showPlayers = !_showPlayers;
    }
}
