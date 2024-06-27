/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** rgif.hpp
*/

#pragma once

#include "raylib-cpp.hpp"
#include <filesystem>
#include <vector>
#include <algorithm>
#include <memory>

#include <thread>
#include <mutex>
#include <atomic>
#include <condition_variable>


namespace raylib {
    class Gif {
    public:
        Gif(void) = default;
        Gif(const Gif &gif)
        {
            // WARNING: This copy constructor will only work for gif file, not folder
            _loop = gif._loop;
            _maxFrameDelay = gif._maxFrameDelay;
            _frameDelay = gif._frameDelay;
            _scale = gif._scale;
            _frameCount = gif._frameCount;
            _currentFrame = gif._currentFrame;
            _animEnded = gif._animEnded;
            _image = gif._image;
            _texture = gif._texture;
        }
        Gif(const std::string &path, bool loop = true, int frameDelay = 2,
            float scale = 1.0f) :
            _loop(loop),
            _maxFrameDelay(frameDelay),
            _frameDelay(frameDelay),
            _scale(scale)
        {
            if (std::filesystem::is_directory(path)) {
                std::vector<std::filesystem::directory_entry> entries;
                for (const auto& entry : std::filesystem::directory_iterator(path)) {
                    entries.push_back(entry);
                }

                if (entries.empty()) {
                    _animEnded = true;
                    return;
                }

                std::sort(entries.begin(), entries.end(),
                    [](const std::filesystem::directory_entry &a,
                    const std::filesystem::directory_entry &b) {
                        return a.path().string() < b.path().string();
                    }
                );

                _frameCount = 0;
                // for (size_t i = 0; i < entries.size(); i++) {
                //     _frameCount++;
                //     _images.push_back(Image(entries[i].path().string()));
                // }
                _images.push_back(Image(entries[0].path().string()));
                _texture = std::make_shared<Texture2D>(_images[0]);
                for (const auto& entry : entries) {
                    _frameCount++;
                    _paths.push_back(entry.path().string());
                }
                _loadThread = std::thread(&Gif::loadTexturesAsync, this);
                _mesh = GenMeshPlane(_texture->width, _texture->height, 1, 1);
                _meshMaterial = LoadMaterialDefault();
                _meshMaterial.maps[MATERIAL_MAP_DIFFUSE].texture = *_texture;
            } else {
                int localFrames;
                _image = std::make_shared<Image>(path, &localFrames);
                _frameCount = localFrames;
                _texture = std::make_shared<Texture2D>(*_image);
            }
            _currentFrame = 0;
            if (loop)
                _animEnded = false;
        }
        ~Gif(void) {
            if (_loadThread.joinable()) {
                _loadThread.join();
            }
        }

        void update(void) {
            if (_animEnded) {
                return;
            }
            if (_frameDelay >= 0) {
                _frameDelay--;
                return;
            }
            if (_images.size() > 0) {
                while(_currentFrame >= _images.size()) {
                    std::this_thread::sleep_for(std::chrono::milliseconds(1));
                }
                _texture->Update(_images[_currentFrame].data);
            }
            _frameDelay = _maxFrameDelay;
            _currentFrame++;
            if (_currentFrame >= _frameCount) {
                if (_loop) {
                    _currentFrame = 0;
                } else {
                    _animEnded = true;
                }
            }
        };
        void draw(const Camera &camera, Vector3 position, float scale = 1, raylib::Vector3 angle = {0, 0, 0}) {
            if (_animEnded) {
                return;
            }

            scale *= _scale;
            if (_images.size() > 0) {
                _mesh.Draw(_meshMaterial, Matrix::Scale(scale, scale, scale) * Matrix::RotateXYZ(angle) * Matrix::Translate(position.x, position.y, position.z));
            } else {
                unsigned int nextFrameDataOffset = _image->width * _image->height * 4 * _currentFrame;

                _texture->Update(((unsigned char *)_image->data) + nextFrameDataOffset);
                _texture->DrawBillboard(camera, position, scale);
            }
        }

        void reset(bool animEnded = false) {
            _currentFrame = 0;
            _animEnded = false;
        }

        bool isAnimEnded(void) const {
            return _animEnded;
        }

    private:
        // Threads
        void loadTexturesAsync() {
            for (size_t i = 0; i < _paths.size(); ++i) {
                std::lock_guard<std::mutex> lock(_textureMutex);
                _images.push_back(Image(_paths[i]));

                // _textureCondition.notify_one();
            }
            // _texturesLoaded = true;
        }

        // void ensureCurrentTextureLoaded() {
        //     _textureMutex.lock();
        //     // std::unique_lock<std::mutex> lock(_textureMutex);
        //     while (_currentFrame >= _images.size()) {
        //         // _textureCondition.wait(lock);
        //     }
        // }

        // From file
        std::shared_ptr<Image> _image;
        std::shared_ptr<Texture2D> _texture;

        // From folder
        std::vector<Image> _images;
        std::vector<std::string> _paths;
        Mesh _mesh;
        Material _meshMaterial;
        // Threading folder loading
        std::thread _loadThread;
        std::mutex _textureMutex;
        std::condition_variable _textureCondition;
        // std::atomic<bool> _texturesLoaded {false};

        bool _loop;
        bool _animEnded = true;

        size_t _frameCount;
        size_t _currentFrame;

        int _maxFrameDelay;
        int _frameDelay;

        float _scale = 1.0f;
    };
}
