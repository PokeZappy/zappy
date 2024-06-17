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
        raylib::Vector3 pos(0, 0, 0);
        _window.SetTargetFPS(60);
    }

    void Raylib::render(const World &world)
    {
        raylib::Color textColor = raylib::Color::Red();
        _window.BeginDrawing();
        {
            _window.ClearBackground(RAYWHITE);
            _window.DrawFPS();
            _camera.BeginMode();
            DrawGrid(30, 100);
            _camera.EndMode();
            textColor.DrawText("bonsoir", 50, 500, 50);
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

    void Raylib::update()
    {
        _camera.Update(CAMERA_FIRST_PERSON);
        return;
    }

    bool Raylib::isOpen()
    {
        return (!_window.ShouldClose());
    }
}