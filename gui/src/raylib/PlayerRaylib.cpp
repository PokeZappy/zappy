/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** PlayerRaylib.cpp
*/

#include "PlayerRaylib.hpp"
#include <chrono>

namespace Zappy
{
    PlayerRaylib::PlayerRaylib(
        const std::shared_ptr<Player> worldPlayer, PokemonInfo &pkInfo,
        std::shared_ptr<RaylibModels> models, float gridSize,
        const raylib::Gif &broadcastGif, const raylib::Gif &successGif,
        const raylib::Gif &failureGif, const raylib::Gif &followGif,
        const raylib::Gif &pushGif) :
        AEntityRaylib(gridSize),
        worldPlayer(worldPlayer),
        _broadcastGif(broadcastGif),
        _successGif(successGif),
        _failureGif(failureGif),
        _followGif(followGif),
        _pushGif(pushGif)
    {
        _models = models;
        _scale = _gridSize / 32;
        _height = _gridSize;
        color = raylib::Color::White();
        infos = pkInfo;



        offset = raylib::Vector2(
                Utils::generateRandomFloat(gridSize / 3),
                Utils::generateRandomFloat(gridSize / 3));
        _currentPos = raylib::Vector2(worldPlayer->getX(), worldPlayer->getY());

        // TraceLog(LOG_ERROR, "%i", _animationIndexes["walk"]);

        _height += (rand() % 20) * _gridSize / 20;
    }

    void PlayerRaylib::updateModels(std::shared_ptr<RaylibModels> models)
    {
        _models = models;
    }

    float PlayerRaylib::getRotation(void) const
    {
        switch (worldPlayer->getOrientation()) {
        case Orientation::NORTH: return 180;
        case Orientation::EAST: return 270;
        case Orientation::SOUTH: return 0;
        case Orientation::WEST: return 90;
        default: return 0;
        }
        return 0;
    }

    raylib::Vector3 PlayerRaylib::getPixelPos(void) const
    {
        return raylib::Vector3(
            _currentPos.x * _gridSize + offset.x,
            _altitude + std::abs(_verticalRotation * _gridSize / 10.f),
            _currentPos.y * _gridSize + offset.y
        );
    }

    void PlayerRaylib::update(void)
    {
        if (worldPlayer->getIncantationState() == Incantation::INCANTING) {
            auto currentTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()) / 1000.;
            _verticalRotation = sin(currentTime.count() * 2) * 10;
        } else {
            _verticalRotation = 0;
        }

        // die
        if (_isDying) {
            move(raylib::Vector3((float)(rand() % 3 - 1) / 20,
                _altitude * 1.04 + _gridSize * 0.01, (float)(rand() % 3 - 1) / 20));
            _scale *= 0.997;
        }

        if (_altitude <= 0) {
            _altitude = 0;
        }
        raylib::Vector2 posGoal(worldPlayer->getX(), worldPlayer->getY());
        raylib::Vector2 deltaMove((posGoal - _currentPos) / 20);

        _currentPos += deltaMove;
        bool isMoving = deltaMove.x != 0 || deltaMove.y != 0;
        if (isMoving) {
            _animFrame++;
        }
        if (_models->hasAnim(Animations::WALK))
            _animIndex = Animations::WALK;
        if (std::abs(_currentPos.x - posGoal.x) < 0.01 && std::abs(_currentPos.y - posGoal.y) < 0.01) {
            _currentPos = posGoal;
        }
        if (_hasIdleAnim && _currentPos == posGoal) {
            if (_models->hasAnim(Animations::IDLE)) {
                _animIndex = Animations::IDLE;
            }
        }
        if (worldPlayer->getIncantationState() != _graphicalIncantingState) {
            _graphicalIncantingState = worldPlayer->getIncantationState();
            if (_graphicalIncantingState == Incantation::SUCCESS) {
                _successGif.reset();
            } else if (_graphicalIncantingState == Incantation::FAILURE) {
                _failureGif.reset();
            }
        }
        if (worldPlayer->getBroadcast() != _broadcastMessage) {
            _broadcastMessage = worldPlayer->getBroadcast();
            _broadcastGif.reset();
        }
        if (worldPlayer->isPushing()) {
            _pushGif.reset();
        }
        _successGif.update();
        _failureGif.update();
        _broadcastGif.update();
        _pushGif.update();

        if (_animatedScale < _scale) {
            _animatedScale += (_scale - _animatedScale) / 1000. + _gridSize / 1000.;
        }
    }

    void PlayerRaylib::draw(void)
    {
        float rotationGoal = getRotation();
        _currentOrientation += (rotationGoal - _currentOrientation) / 5;

        // draw
        // TODO: à verifier mais cette ligne causera surement des comportements indéfinis si animIndex vaut -1, donc penser à ce cas
        // if (_animIndex != NONE) {
        //     _model->updateAnimation(_animIndex, _animFrame);
        // }

        if (infos.shiny) {
            _models->setShinyTexture(_animIndex);
        } else {
            _models->setNormalTexture(_animIndex);
        }
        _models->getModelByAnimation(_animIndex)->draw(getPixelPos(),
            raylib::Vector3(_verticalRotation, 1, 0),
            _currentOrientation + (std::abs(_verticalRotation * 50) * worldPlayer->getLevel() / 2.),
            raylib::Vector3(_animatedScale, true) * (1 + _level / 2.0f));
    }

    void PlayerRaylib::drawGifs(const Camera &camera)
    {
        raylib::Vector3 gifPos = getPixelPos() + raylib::Vector3(0, _gridSize, 0);
        _broadcastGif.draw(camera, gifPos);
        _successGif.draw(camera, gifPos);
        _failureGif.draw(camera, gifPos);
        _pushGif.draw(camera, gifPos);
    }

    void PlayerRaylib::drawFollowGif(const Camera &camera)
    {
        raylib::Vector3 gifPos = getPixelPos() + raylib::Vector3(0, _gridSize / 1.5, 0);
        _followGif.update();
        _followGif.draw(camera, gifPos);
    }

    void PlayerRaylib::glow(void)
    {
        // Material *material = &_models->getModelByAnimation(_animIndex)->getModel().materials[1];
        // std::cout << "-- Albedo -- color:" << raylib::Color(material->maps[MATERIAL_MAP_ALBEDO].color).ToString() << ", value: "
        //             << std::to_string(material->maps[MATERIAL_MAP_ALBEDO].value) << std::endl;
        // material->maps[MATERIAL_MAP_ALBEDO].value = 0.5;
        // material->maps[MATERIAL_MAP_DIFFUSE].value = 0.2;
    }
} // namespace Zappy
