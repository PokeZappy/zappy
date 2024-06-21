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
        _sun(raylib::Model(SUN_MODEL_PATH)),
        _moon(raylib::Model(MOON_MODEL_PATH)),
        _tv(raylib::Model(GAMEBOY_MODEL_PATH)),
        _arena(raylib::Model(ARENA_MODEL_PATH)),
        _rockModel(raylib::Model(POKEBALL_MODEL_PATH)),
        _foodModel(raylib::Model(FOOD_MODEL_PATH)),
        _shader(raylib::Shader::Load("assets/shaders/lighting.vs", "assets/shaders/lighting.fs")
        )
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
        float ambientLight = 0.8f;
        float array[4] = { ambientLight, ambientLight, ambientLight, 1.0f };
        SetShaderValue(_shader, ambientLoc, array, SHADER_UNIFORM_VEC4);
        debugMode = std::make_unique<DebugMode>();
        _hudMode = std::make_unique<HudMode>();
        _window.ToggleFullscreen();

        // Create lights
        float lightHeight = 100.0f;
        float extremity = _gridSize * 30;
        _lights[0] = CreateLight(LIGHT_POINT, (Vector3){ extremity, lightHeight, extremity }, Vector3Zero(), SUN_COLOR, _shader);
        _lights[1] = CreateLight(LIGHT_POINT, (Vector3){ 0, lightHeight, extremity }, Vector3Zero(), MOON_COLOR, _shader);
        // _lights[2] = CreateLight(LIGHT_POINT, (Vector3){ extremity, lightHeight, 0 }, Vector3Zero(), GREEN, _shader);
        // _lights[3] = CreateLight(LIGHT_POINT, (Vector3){ 0, lightHeight, 0 }, Vector3Zero(), BLUE, _shader);

        // -- Camera --
        // _camera.SetPosition(Vector3{(81.0F), (35.0F), (68.0F)});
        // _camera.SetTarget(Vector3{(305.0F), (-60.0F), (-10.0F)});

        _camera.SetPosition(Vector3{(215.0F), (55.0F), (600.0F)});
        _camera.SetTarget(Vector3{(223.0F), (1.0F), (350.0F)});
        // 30x30
        // _camera.SetPosition(Vector3{(789.0F), (148.0F), (1609.0F)});
        // _camera.SetTarget(Vector3{(817.0F), (74.0F), (1365.0F)});
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
        for (int i = 0; i < _arena.materialCount; i++)
            _arena.materials[i].shader = _shader;

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
        _listTypes = {"grass", "fire", "water",
                      "steel", "dragon", "electric",
                      "bug", "psychic", "ground",
                      "dark", "fight", "fairy",
                      "ice", "normal", "poison",
                      "rock", "ghost", "fly",
                      "eevee", "mustebeh"};
        _listTypesColors = {
            (Color){107, 190, 48}, (Color){231, 59, 12}, (Color){48, 144, 241},
            (Color){179, 179, 194}, (Color){113, 89, 215}, (Color){250, 179, 21},
            (Color){148, 162, 18}, (Color){234, 67, 125}, (Color){203, 171, 82},
            (Color){79, 57, 43}, (Color){126, 50, 26}, (Color){239, 172, 241},
            (Color){126, 218, 244}, (Color){197, 191, 180}, (Color){146, 66, 144},
            (Color){181, 161, 88}, (Color){89, 92, 169}, (Color){138, 159, 239},
            raylib::Color::White(), raylib::Color::Orange(),
        };

        // -- Eggs --
        _eggModelAnimations = raylib::ModelAnimation::Load(EGG_MODEL_PATH);

        _moon.materials[1].shader = _shader;

        _arenaAltitudeScale = -(1. / 10.);
        _arenaScale = 40;
        getArenaOffset = [](size_t tileCount, size_t gridSize) -> float {
            float correction = tileCount % 2 == 0 ? gridSize / 2 : 0;
            return tileCount / 2 * gridSize - correction;
        };
    }
}
