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

        _camera.SetPosition(Vector3{(247.0F), (125.0F), (710.0F)});
        _camera.SetTarget(Vector3{(305.0F), (-60.0F), (-10.0F)});

        // Load floor texture
        _floorTexture = raylib::Texture2D("assets/textures/pokemon_tile.png");
        _floorMesh = GenMeshPlane(GRID_SIZE, GRID_SIZE, 1, 1);
        _floorMaterial = LoadMaterialDefault();
        _floorMaterial.maps[MATERIAL_MAP_DIFFUSE].texture = _floorTexture;

        _tv = raylib::Model("assets/models/nintendo_game_boy.glb");
    }

    void Raylib::render(const World &world)
    {
        (void)world;
        raylib::Color textColor = raylib::Color::Black();
        _window.BeginDrawing();
        {
            _window.ClearBackground(raylib::Color::SkyBlue());
            _window.DrawFPS();
            // 3D scene

            _camera.BeginMode();
            for (int x = 0; x < 10; x++) {
                for (int z = 0; z < 10; z++) {
                    DrawMesh(_floorMesh, _floorMaterial, MatrixTranslate(x * GRID_SIZE, 0.0f, z * GRID_SIZE));
                }
            }

            for (auto &player : _players) {
                player.draw();
            }

            _tv.Draw(raylib::Vector3(_mapX / 2 * GRID_SIZE - 50, 80, - GRID_SIZE * 4), 2000);

            _camera.EndMode();
            // end of 3D scene
            textColor.DrawText(raylib::Vector3(_camera.GetPosition()).ToString(), 50, 50, 25);
            textColor.DrawText(raylib::Vector3(_camera.GetTarget()).ToString(), 50, 80, 25);
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
            _camera.position.y += 1;
            _camera.target.y += 1;
        }
        if (IsKeyDown(KEY_LEFT_SHIFT)) {
            _camera.position.y -= 1;
            _camera.target.y -= 1;
        }
        _camera.Update(CAMERA_FIRST_PERSON);
        for (const auto &player : world.getPlayers()) {
            if (!containsPlayer(player))
                _players.push_back(PlayerRaylib(player, "assets/models/pokemons/torterra.glb"));
        }
    }

    bool Raylib::isOpen()
    {
        return (!_window.ShouldClose());
    }
}
