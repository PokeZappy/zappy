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
        std::shared_ptr<RaylibModels> models, float gridSize, raylib::Color teamColor,
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
        infos = pkInfo;
        color = teamColor;

        offset = raylib::Vector2(
                Utils::generateRandomFloat(gridSize / 3),
                Utils::generateRandomFloat(gridSize / 3));
        _currentPos = raylib::Vector2(worldPlayer->getX(), worldPlayer->getY());

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

    void PlayerRaylib::drawPantheon(raylib::Vector3 position) {
        if (infos.shiny) {
            _models->setShinyTexture(_animIndex);
        } else {
            _models->setNormalTexture(_animIndex);
        }

        _models->getModelByAnimation(Animations::PANTHEON)->draw(position,
            raylib::Vector3(0, 1, 0),
            90,
            raylib::Vector3(_gridSize / 12, true) * (1 + worldPlayer->getLevel() / 4.0f),
            raylib::Color::White()
        );
    }

    void PlayerRaylib::draw(bool tintWithTeamColor)
    {
        float rotationGoal = getRotation();
        _currentOrientation += (rotationGoal - _currentOrientation) / 5;

        if (infos.shiny) {
            _models->setShinyTexture(_animIndex);
        } else {
            _models->setNormalTexture(_animIndex);
        }
        _models->getModelByAnimation(_animIndex)->draw(getPixelPos(),
            raylib::Vector3(_verticalRotation, 1, 0),
            _currentOrientation + (std::abs(_verticalRotation * 50) * worldPlayer->getLevel() / 2.),
            raylib::Vector3(_animatedScale, true) * (1 + worldPlayer->getLevel() / 2.0f),
            tintWithTeamColor ? color : raylib::Color::White());
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
} // namespace Zappy
