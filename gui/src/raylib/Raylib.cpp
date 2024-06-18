/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** Raylib.cpp
*/

#include "Raylib.hpp"

namespace Zappy
{
    Raylib::Raylib() : _window(GUI_WIDTH, GUI_HEIGHT, "Zappy"),
        _camera(Vector3{(10.0F), (100.0F), (10.0F)}, Vector3{(0.0F), (0.0F), (0.0F)}, Vector3{(0.0F), (1.0F), (0.0F)}, 45.0f),
        _shader(raylib::Shader::Load(nullptr, "assets/discard_alpha.fs"))
    {
        _window.SetTargetFPS(60);

        _camera.SetPosition(Vector3{(247.0F), (125.0F), (710.0F)});
        _camera.SetTarget(Vector3{(305.0F), (-60.0F), (-10.0F)});

        // Load floor texture
        _floorTexture = raylib::Texture2D("assets/textures/pokemon_tile.png");
        _floorMesh = GenMeshPlane(_gridSize, _gridSize, 1, 1);
        _floorMaterial = LoadMaterialDefault();
        _floorMaterial.maps[MATERIAL_MAP_DIFFUSE].texture = _floorTexture;

        _tv = raylib::Model("assets/models/nintendo_game_boy.glb");

        // Rocks
        std::string pokeballModelPath = "assets/models/poke_ball.glb";
        _rockModel = raylib::Model(pokeballModelPath);
        _rockTextures.push_back(LoadTexture("assets/textures/pokeball/poke_ball.png"));
        _rockTextures.push_back(LoadTexture("assets/textures/pokeball/great_ball.png"));
        _rockTextures.push_back(LoadTexture("assets/textures/pokeball/ultra_ball.png"));
        _rockTextures.push_back(LoadTexture("assets/textures/pokeball/premier_ball.png"));
        _rockTextures.push_back(LoadTexture("assets/textures/pokeball/luxury_ball.png"));
        _rockTextures.push_back(LoadTexture("assets/textures/pokeball/master_ball.png"));
        _rockAnimations = raylib::ModelAnimation::Load(pokeballModelPath);

        // Food
        _foodModel = raylib::Model("assets/models/pecha_berry.glb");
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

            for (int x = 0; x < _mapX; x++) {
                for (int z = 0; z < _mapY; z++) {
                    DrawMesh(_floorMesh, _floorMaterial, MatrixTranslate(x * _gridSize, 0.0f, z * _gridSize));
                }
            }

            drawTiles(world.getTiles());

            for (auto &player : _players) {
                player->draw();
            }

            _tv.Draw(raylib::Vector3(_mapX / 2 * _gridSize - 50, 80, -(float)(_gridSize * 4)), 2000);

            _camera.EndMode();
            // end of 3D scene
            textColor.DrawText(raylib::Vector3(_camera.GetPosition()).ToString(), 50, 50, 25);
            textColor.DrawText(raylib::Vector3(_camera.GetTarget()).ToString(), 50, 80, 25);
        }
        _window.EndDrawing();
    }

    bool Raylib::containsPlayer(std::shared_ptr<Player> player)
    {
        for (const auto &playerRaylib : _players) {
            if (playerRaylib->worldPlayer == player) {
                return true;
            }
        }
        return false;
    }

    void Raylib::update(const World &world)
    {
        _mapX = world._mapX;
        _mapY = world._mapY;
        if (IsKeyDown(KEY_SPACE)) {
            _camera.position.y += 1;
            _camera.target.y += 1;
        }
        if (IsKeyDown(KEY_LEFT_SHIFT)) {
            _camera.position.y -= 1;
            _camera.target.y -= 1;
        }

        // Update Graphical Player list
        _camera.Update(CAMERA_FIRST_PERSON);
        for (const auto &player : world.getPlayers()) {
            if (!containsPlayer(player))
                _players.push_back(std::make_unique<PlayerRaylib>(player, "assets/models/pokemons/torterra.glb", _gridSize));
        }
        size_t decal = 0;
        for (size_t i = 0; i < _players.size(); i++) {
            if (!world.containsPlayer(_players[i - decal]->worldPlayer->getId())) {
                _players[i]->kill();
            }
            _players[i]->update();
            if (_players[i]->getHeight() > 2000) {
                _players.erase(_players.begin() + i - decal);
                decal++;
            }
        }
    }

    bool Raylib::isOpen()
    {
        return (!_window.ShouldClose());
    }
}
