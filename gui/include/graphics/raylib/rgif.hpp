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
#include <regex>

namespace raylib {
    static bool naturalOrderCompare(const std::filesystem::directory_entry& entryA, const std::filesystem::directory_entry& entryB) {
        static const std::regex regexPattern(R"((\d+)|(\D+))");
        const std::string fileNameA = entryA.path().filename().string();
        const std::string fileNameB = entryB.path().filename().string();

        std::sregex_token_iterator iteratorA(fileNameA.begin(), fileNameA.end(), regexPattern);
        std::sregex_token_iterator iteratorB(fileNameB.begin(), fileNameB.end(), regexPattern);
        std::sregex_token_iterator end;

        while (iteratorA != end && iteratorB != end) {
            const std::string tokenA = iteratorA->str();
            const std::string tokenB = iteratorB->str();

            if (tokenA != tokenB) {
                if (isdigit(tokenA[0]) && isdigit(tokenB[0])) {
                    return std::stoi(tokenA) < std::stoi(tokenB);
                }
                return tokenA < tokenB;
            }
            ++iteratorA;
            ++iteratorB;
        }
        return fileNameA.size() < fileNameB.size();
    }

    class Gif {
    public:
        Gif(void) = default;
        Gif(const std::string &path, bool loop = true, int frameDelay = 2) :
            _loop(loop),
            _maxFrameDelay(frameDelay),
            _frameDelay(frameDelay)
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

                    std::sort(entries.begin(), entries.end(), naturalOrderCompare);

                    _frames = 0;
                    for (size_t i = 0; i < entries.size() && i < 2; i++) {
                        _textures.push_back(Texture2D(entries[i].path().string()));
                    }
                    for (const auto& entry : entries) {
                        _frames++;
                        _paths.push_back(entry.path().string());
                    }
                    _mesh = GenMeshPlane(_textures[0].width, _textures[0].height, 1, 1);
                    _meshMaterial = LoadMaterialDefault();
                    _meshMaterial.maps[MATERIAL_MAP_DIFFUSE].texture = _textures[0];
                    // _meshMaterial.shader = _shader;
                } else {
                    int localFrames;
                    _image.Load(path.c_str(), &localFrames);
                    _frames = localFrames;
                    _texture = Texture2D(_image);

                }
                _currentFrame = 0;
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
            if (_textures.size() > 0 && _textures.size() < _frames) {
                _textures.push_back(Texture2D(_paths[_textures.size()]));
            }
            _frameDelay = _maxFrameDelay;
            _meshMaterial.maps[MATERIAL_MAP_DIFFUSE].texture = _textures[_currentFrame];
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

            if (_textures.size() > 0) {
                // From a single texture with a list of images
                // _texture = Texture2D(_images[_currentFrame]);
                // _texture.DrawBillboard(camera, position, scale);

                // _textures[_currentFrame].DrawBillboard(camera, position, scale);
                _mesh.Draw(_meshMaterial, Matrix::Scale(scale, scale, scale) * Matrix::RotateX(PI / 2) * Matrix::Translate(position.x, position.y, position.z));
            } else {
                unsigned int nextFrameDataOffset = _image.width * _image.height * 4 * _currentFrame;

                _texture.Update(((unsigned char *)_image.data) + nextFrameDataOffset);
                _texture.DrawBillboard(camera, position, scale);
            }

        }

        void reset(void) {
            _currentFrame = 0;
            _animEnded = false;
        }

        bool isAnimEnded(void) const {
            return _animEnded;
        }

    private:
        Image _image;
        Texture2D _texture;
        // std::vector<Image> _images;
        std::vector<Texture2D> _textures;
        std::vector<std::string> _paths;
        Mesh _mesh;
        Material _meshMaterial;

        bool _loop;
        bool _animEnded = true;

        size_t _frames;
        size_t _currentFrame;

        int _maxFrameDelay;
        int _frameDelay;
    };
}
