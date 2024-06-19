/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** init.cpp
*/

#include "Raylib.hpp"

namespace Zappy {
     Raylib::Raylib() : _window(GUI_WIDTH, GUI_HEIGHT, "Zappy"),
        _camera(Vector3{(10.0F), (100.0F), (10.0F)}, Vector3{(0.0F), (0.0F), (0.0F)}, Vector3{(0.0F), (1.0F), (0.0F)}, 45.0f),
        _shader(raylib::Shader::Load(nullptr, "assets/discard_alpha.fs"))
    {
        _window.SetTargetFPS(60);
        try
        {
            _configuration.readFile("assets/pokemons.cfg");
        }
        catch (const libconfig::FileIOException &fioex)
        {
            std::cerr << "Impossible d'ouvrir le fichier de configuration." << std::endl;
        }
        catch (const libconfig::ParseException &pex)
        {
            std::cerr << "Erreur de parsing au fichier " << pex.getFile() << ":"
                      << pex.getLine() << " - " << pex.getError() << std::endl;
        }

        _camera.SetPosition(Vector3{(81.0F), (35.0F), (68.0F)});
        _camera.SetTarget(Vector3{(305.0F), (-60.0F), (-10.0F)});
        DisableCursor();

        // Load floor texture
        _floorTexture = raylib::Texture2D("assets/textures/pokemon_tile.png");
        _floorMesh = GenMeshPlane(_gridSize, _gridSize, 1, 1);
        _floorMaterial = LoadMaterialDefault();
        _floorMaterial.maps[MATERIAL_MAP_DIFFUSE].texture = _floorTexture;

        _hitGridTexture = raylib::Texture2D("assets/textures/pokemon_hit_tile.png");
        _hitGridMaterial = LoadMaterialDefault();
        _hitGridMaterial.maps[MATERIAL_MAP_DIFFUSE].texture = _hitGridTexture;

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
        listTypes = {"grass", "fire", "water", "steel", "dragon", "electric", "bug", "psychic", "ground", "dark", "fight", "fairy", "ice", "normal", "poison", "rock", "ghost", "fly", "eevee"};
    }
}