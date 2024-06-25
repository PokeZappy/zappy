/*
** EPITECH PROJECT, 2023
** gui
** File description:
** Skybox.cpp
*/

#include "Skybox.hpp"
#include <iostream>
#include "Utils.hpp"
namespace Zappy {
    Skybox::Skybox(const std::string &assetsRoot) {
    raylib::Mesh cube = GenMeshCube(1.0f, 1.0f, 1.0f);
	_skybox = LoadModelFromMesh(cube);
	_skybox.materials[0].shader = raylib::Shader(assetsRoot + "shaders/skybox.vert", assetsRoot + "shaders/skybox.frag");
	_daytimeLoc = GetShaderLocation(_skybox.materials[0].shader, "daytime");
	_dayrotationLoc = GetShaderLocation(_skybox.materials[0].shader, "dayrotation");
	float skyboxMoveFactor = 0.0f;
	_moveFactorLoc = GetShaderLocation(_skybox.materials[0].shader, "moveFactor");
	// raylib::Shader shdrCubemap = LoadShader((assetsRoot + "shaders/cubemap.vert").c_str(), (assetsRoot + "shaders/cubemap.frag").c_str());
	int param[1] = { MATERIAL_MAP_CUBEMAP };
	SetShaderValue(_skybox.materials[0].shader, GetShaderLocation(_skybox.materials[0].shader, "environmentMapNight"), param, SHADER_UNIFORM_INT);
	int param2[1] = { MATERIAL_MAP_IRRADIANCE };
	SetShaderValue(_skybox.materials[0].shader, GetShaderLocation(_skybox.materials[0].shader, "environmentMapDay"), param2, SHADER_UNIFORM_INT);
	int param3[1] = { 0 };
	// SetShaderValue(shdrCubemap, GetShaderLocation(shdrCubemap, "equirectangularMap"), param3, SHADER_UNIFORM_INT);
	Texture2D texHDR = LoadTexture((assetsRoot + "textures/skybox/milkyWay.hdr").c_str()); // Load HDR panorama (sphere) texture
	Texture2D texHDR2 = LoadTexture((assetsRoot + "textures/skybox/daytime.hdr").c_str()); // Load HDR panorama (sphere) texture
    Image imageHDR = LoadImage((assetsRoot + "textures/skybox/milkyWay.hdr").c_str());
    Image imageHDR2 = LoadImage((assetsRoot + "textures/skybox/daytime.hdr").c_str());
	// Generate cubemap (texture with 6 quads-cube-mapping) from panorama HDR texture
	// NOTE: New texture is generated rendering to texture, shader computes the sphere->cube coordinates mapping
	_skybox.materials[0].maps[0].texture = LoadTexture((assetsRoot + "textures/skybox/skyGradient.png").c_str());
	SetTextureFilter(_skybox.materials[0].maps[0].texture, TEXTURE_FILTER_BILINEAR);
	SetTextureWrap(_skybox.materials[0].maps[0].texture, TEXTURE_WRAP_CLAMP);
	_skybox.materials[0].maps[MATERIAL_MAP_CUBEMAP].texture = LoadTextureCubemap(imageHDR, CUBEMAP_LAYOUT_AUTO_DETECT);
	_skybox.materials[0].maps[MATERIAL_MAP_IRRADIANCE].texture = LoadTextureCubemap(imageHDR2, CUBEMAP_LAYOUT_AUTO_DETECT);
	SetTextureFilter(_skybox.materials[0].maps[MATERIAL_MAP_CUBEMAP].texture, TEXTURE_FILTER_BILINEAR);
	SetTextureFilter(_skybox.materials[0].maps[MATERIAL_MAP_IRRADIANCE].texture, TEXTURE_FILTER_BILINEAR);
	GenTextureMipmaps(&_skybox.materials[0].maps[MATERIAL_MAP_CUBEMAP].texture);
	GenTextureMipmaps(&_skybox.materials[0].maps[MATERIAL_MAP_IRRADIANCE].texture);
	SetShaderValue(_skybox.materials[0].shader, _daytimeLoc, 0, SHADER_UNIFORM_INT);
	SetShaderValue(_skybox.materials[0].shader, _dayrotationLoc, 0, SHADER_UNIFORM_INT);

    UnloadImage(imageHDR);
    UnloadImage(imageHDR2);
	UnloadTexture(texHDR);      // Texture not required anymore, cubemap already generated
	UnloadTexture(texHDR2);      // Texture not required anymore, cubemap already generated
	// UnloadShader(shdrCubemap);  
    }

    void Skybox::draw() {

        _moveFactor += 0.0085f * GetFrameTime();
		while (_moveFactor > 1.0f)
		{
			_moveFactor -= 1.0;
		}
		// SetShaderValue(_skybox.materials[0].shader, _moveFactorLoc, &_moveFactor, SHADER_UNIFORM_FLOAT);

        _daytime += 0.02 * GetFrameTime();
        while (_daytime > 1.0f)
        {
            _daytime -= 1.0;
        }
		float sunAngle = Lerp(-90, 270, _daytime) * DEG2RAD; // -90 midnight, 90 midday
        float ndaytime = sinf(sunAngle);
        SetShaderValue(_skybox.materials[0].shader, _daytimeLoc, &ndaytime, SHADER_UNIFORM_FLOAT);
		SetShaderValue(_skybox.materials[0].shader, _dayrotationLoc, &_daytime, SHADER_UNIFORM_FLOAT);
        DrawModel(_skybox, (Vector3){0, 0, 0}, 0.0001f, WHITE);

    }
}