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
            if (IsKeyPressed(KEY_ESCAPE)) {
                if (_pantheon->activated()) {
                    _pantheonTheme.Stop();
                    _mainTheme.Play();
                    _pantheon->desactivate();
                }
                if (!debugMode->activated())
                    _escapeMenu->switchState();
            }
        }
        if (_menuState != Menu::NONE || _escapeMenu->activated() || _pantheon->activated())
            return;
        // Pantheon key
        // if (!debugMode->activated() && IsKeyPressed(KEY_P)) {
        //     _mainTheme.Stop();
        //     _pantheonTheme.Play();
        //     _pantheon->activate("grass", getTeamColor("grass"), _players);
        // }
        if (debugMode->getType() != CHAT && (!_hudMode->isChatEnabled())) {
            
            if (IsKeyDown(KEY_SPACE)) {
                _camera.position.y += moveYSpeed;
                _camera.target.y += moveYSpeed;
            }
            if (IsKeyDown(KEY_LEFT_SHIFT)) {
                _camera.position.y -= moveYSpeed;
                _camera.target.y -= moveYSpeed;
            }

            if (IsKeyPressed(KEY_N)) {
                _hudMode->switchState();
                _cameraViewMode = CAMERA_FIRST_PERSON;
            }

            if (IsKeyPressed(KEY_G)) {
                if (debugMode->activated()) {
                    _defaultCameraPosition = raylib::Vector3((_gridSize * _mapX) / 2, _gridSize, (_gridSize * _mapY) / 2);
                    _defaultCameraTarget = raylib::Vector3((_gridSize * _mapX) / 2, _gridSize, _gridSize * (_mapY));
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
            }
        }

        // Update the shader with the camera view vector (points towards { 0.0f, 0.0f, 0.0f })
        float cameraPos[3] = { _camera.position.x, _camera.position.y, _camera.position.z };
        SetShaderValue(_shader, _shader.locs[SHADER_LOC_VECTOR_VIEW], cameraPos, SHADER_UNIFORM_VEC3);

        // Check key inputs to enable/disable lights
        // if (IsKeyPressed(KEY_Y)) { _lights[0].enabled = !_lights[0].enabled; }
        // if (IsKeyPressed(KEY_R)) { _lights[1].enabled = !_lights[1].enabled; }
        // if (IsKeyPressed(KEY_G)) { _lights[2].enabled = !_lights[2].enabled; }
        // if (IsKeyPressed(KEY_B)) { _lights[3].enabled = !_lights[3].enabled; }
    }
}
