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
        _eggModel(raylib::Model(EGG_MODEL_PATH)),
        _tv(raylib::Model(GAMEBOY_MODEL_PATH)),
        _rockModel(raylib::Model(POKEBALL_MODEL_PATH)),
        _foodModel(raylib::Model(FOOD_MODEL_PATH)),
        _shader(raylib::Shader::Load("assets/shaders/lighting.vs", "assets/shaders/lighting.fs"))
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

        // -- Shader Lighting --
        SetConfigFlags(FLAG_MSAA_4X_HINT);  // Enable Multi Sampling Anti Aliasing 4x (if available)
        _shader.locs[SHADER_LOC_VECTOR_VIEW] = GetShaderLocation(_shader, "viewPos");
        // Ambient light level (some basic lighting)
        int ambientLoc = GetShaderLocation(_shader, "ambient");
        SetShaderValue(_shader, ambientLoc, (float[4]){ 0.15f, 0.15f, 0.15f, 1.0f }, SHADER_UNIFORM_VEC4);

        _lights->enabled = true;

        // Create lights
        float lightHeight = 100.0f;
        float extremity = _gridSize * 10;
        _lights[0] = CreateLight(LIGHT_POINT, (Vector3){ extremity, lightHeight, extremity }, Vector3Zero(), YELLOW, _shader);
        _lights[1] = CreateLight(LIGHT_POINT, (Vector3){ 0, lightHeight, extremity }, Vector3Zero(), RED, _shader);
        _lights[2] = CreateLight(LIGHT_POINT, (Vector3){ extremity, lightHeight, 0 }, Vector3Zero(), GREEN, _shader);
        _lights[3] = CreateLight(LIGHT_POINT, (Vector3){ 0, lightHeight, 0 }, Vector3Zero(), BLUE, _shader);

        // -- Camera --
        _camera.SetPosition(Vector3{(81.0F), (35.0F), (68.0F)});
        _camera.SetTarget(Vector3{(305.0F), (-60.0F), (-10.0F)});
        // DisableCursor();

        // Load floor texture
        _floorTexture = raylib::Texture2D("assets/textures/pokemon_tile.png");
        _floorMesh = GenMeshPlane(_gridSize, _gridSize, 1, 1);
        _floorMaterial = LoadMaterialDefault();
        _floorMaterial.maps[MATERIAL_MAP_DIFFUSE].texture = _floorTexture;
        _floorMaterial.shader = _shader;

        _hitGridTexture = raylib::Texture2D("assets/textures/pokemon_hit_tile.png");
        _hitGridMaterial = LoadMaterialDefault();
        _hitGridMaterial.maps[MATERIAL_MAP_DIFFUSE].texture = _hitGridTexture;

        _tv.materials[2].shader = _shader;

        // -- Rocks --
        _rockTextures.push_back(LoadTexture("assets/textures/pokeball/poke_ball.png"));
        _rockTextures.push_back(LoadTexture("assets/textures/pokeball/great_ball.png"));
        _rockTextures.push_back(LoadTexture("assets/textures/pokeball/ultra_ball.png"));
        _rockTextures.push_back(LoadTexture("assets/textures/pokeball/premier_ball.png"));
        _rockTextures.push_back(LoadTexture("assets/textures/pokeball/luxury_ball.png"));
        _rockTextures.push_back(LoadTexture("assets/textures/pokeball/master_ball.png"));
        _rockAnimations = raylib::ModelAnimation::Load(POKEBALL_MODEL_PATH);
        _rockModel.materials[1].shader = _shader;

        // -- Food --
        _foodModel.materials[1].shader = _shader;
        listTypes = {"grass", "fire", "water", "steel", "dragon", "electric", "bug", "psychic", "ground", "dark", "fight", "fairy", "ice", "normal", "poison", "rock", "ghost", "fly", "eevee"};

        // -- Eggs --
        _eggModelAnimations = raylib::ModelAnimation::Load(EGG_MODEL_PATH);
    }
}
