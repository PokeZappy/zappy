/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** rgif.hpp
*/

#pragma once

#include "raylib-cpp.hpp"

namespace raylib {
    class Gif {
    public:
        Gif(const std::string &path, bool loop = true, int frameDelay = 2) :
            _image(path.c_str(), &_frames),
            _texture(_image),
            _loop(loop),
            _currentFrame(_frames),
            _maxFrameDelay(frameDelay),
            _frameDelay(frameDelay)
            {
                if (loop)
                    _animEnded = false;
            }

        void update(void) {
            if (_animEnded) {
                return;
            }
            if (_frameDelay >= 0) {
                _frameDelay--;
                return;
            }
            _frameDelay = _maxFrameDelay;
            _currentFrame++;
            if (_currentFrame >= _frames) {
                if (_loop) {
                    _currentFrame = 0;
                } else {
                    _animEnded = true;
                }
            }
        };
        void draw(const Camera &camera, Vector3 position, float scale) {
            if (_animEnded) {
                return;
            }
            unsigned int nextFrameDataOffset = _image.width * _image.height * 4 * _currentFrame;

            _texture.Update(((unsigned char *)_image.data) + nextFrameDataOffset);
            _texture.DrawBillboard(camera, position, scale);
        }

        void reset(void) {
            _currentFrame = 0;
            _animEnded = false;
        }

    private:
        Image _image;
        Texture2D _texture;

        bool _loop;
        bool _animEnded = true;

        int _frames;
        int _currentFrame;

        int _maxFrameDelay;
        int _frameDelay;
    };
}
