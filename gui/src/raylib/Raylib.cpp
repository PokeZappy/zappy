/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** Raylib.cpp
*/

#include "Raylib.hpp"

namespace Zappy
{
    Raylib::Raylib() : _window(GUI_WIDTH, GUI_HEIGHT, "Zappy"), _camera(Vector3{(10.0F), (100.0F), (10.0F)}, Vector3{(0.0F), (0.0F), (0.0F)}, Vector3{(0.0F), (1.0F), (0.0F)}, 45.0f)
    {
        _window.SetTargetFPS(60);

        // Load floor texture
        _floorTexture = raylib::Texture2D("assets/floor4.png");
        _floorMesh = GenMeshPlane(GRID_SIZE, GRID_SIZE, 1, 1);
        _floorMaterial = LoadMaterialDefault();
        _floorMaterial.maps[MATERIAL_MAP_DIFFUSE].texture = _floorTexture;
    }

    void Raylib::render(const World &world)
    {
        (void)world;
        raylib::Color textColor = raylib::Color::Black();
        _window.BeginDrawing();
        {
            _window.ClearBackground(RAYWHITE);
            _window.DrawFPS();
            // 3D scene

            _camera.BeginMode();
            for (int x = 0; x < 10; x++) {
                for (int z = 0; z < 10; z++) {
                    DrawMesh(_floorMesh, _floorMaterial, MatrixTranslate(x * GRID_SIZE, 0.0f, z * GRID_SIZE));
                }
            }

            for (const auto &player : _players) {
                player.draw();
            }

            _camera.EndMode();
            // end of 3D scene
            textColor.DrawText(raylib::Vector3(_camera.GetPosition()).ToString(), 50, 50, 25);
        }
        _window.EndDrawing();
    }

    void Raylib::drawTiles(const std::vector<std::vector<Tile>> &tiles)
    {
        return;
    }

    void Raylib::drawEntity(const std::shared_ptr<IEntity> entity)
    {
        return;
    }

    bool Raylib::containsPlayer(std::shared_ptr<Player> player)
    {
        for (const auto &playerRaylib : _players) {
            if (playerRaylib.worldPlayer == player) {
                return true;
            }
        }
        return false;
    }

    void Raylib::update(const World &world)
    {
        if (IsKeyDown(KEY_SPACE)) {
            _camera.position.y += 0.5f;
            _camera.target.y += 0.5f;
        }
        if (IsKeyDown(KEY_LEFT_SHIFT)) {
            _camera.position.y -= 0.5f;
            _camera.target.y -= 0.5f;
        }
        _camera.Update(CAMERA_FIRST_PERSON);
        for (const auto &player : world.getPlayers()) {
            if (!containsPlayer(player))
                _players.push_back(PlayerRaylib(player));
        }
    }

    bool Raylib::isOpen()
    {
        return (!_window.ShouldClose());
    }
}