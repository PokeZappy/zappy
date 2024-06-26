/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** init.cpp
*/

#include "Raylib.hpp"
#include <filesystem>
#include <optional>

namespace Zappy {
     Raylib::Raylib(const std::string &assetsRoot, ClientSocket &socket) :
        _assetsRoot(assetsRoot),
        _window(GUI_WIDTH, GUI_HEIGHT, "Zappy"),
        _camera(Vector3{(10.0F), (100.0F), (10.0F)}, Vector3{(0.0F), (0.0F), (0.0F)}, Vector3{(0.0F), (1.0F), (0.0F)}, 45.0f),
        _eggModel(raylib::Model(_assetsRoot + EGG_MODEL_PATH)),
        _sun(raylib::Model(_assetsRoot + SUN_MODEL_PATH)),
        _moon(raylib::Model(_assetsRoot + MOON_MODEL_PATH)),
        _tv(raylib::Model(_assetsRoot + DS_MODEL_PATH)),
        _arena(raylib::Model(_assetsRoot + EGG_MODEL_PATH)),
        _rockModel(raylib::Model(_assetsRoot + POKEBALL_MODEL_PATH)),
        _foodModel(raylib::Model(_assetsRoot + FOOD_MODEL_PATH)),
        _shader(raylib::Shader::Load(_assetsRoot + "shaders/lighting.vs", _assetsRoot + "shaders/lighting.fs")),
        _discardTranspShader(raylib::Shader::Load("", _assetsRoot + "shaders/discard_transparent.fs")),
        _menuClock(std::chrono::steady_clock::now()),
        _broadcastGif(raylib::Gif(_assetsRoot + "gifs/broadcast.gif", false, 0, _gridSize / 2)),
        _successGif(raylib::Gif(_assetsRoot + "gifs/success.gif", false, 0, _gridSize / 2)),
        _failureGif(raylib::Gif(_assetsRoot + "gifs/failure.gif", false, 0, _gridSize / 2)),
        _followGif(raylib::Gif(_assetsRoot + "gifs/follow.gif", true, 1, _gridSize / 3)),
        _pushGif(raylib::Gif(_assetsRoot + "gifs/push.gif", false, 1, _gridSize / 2)),
        _socket(socket)
    {
        _window.SetTargetFPS(60);
        SetExitKey(KEY_DELETE);
        try
        {
            _configuration.readFile((_assetsRoot + "pokemons.cfg").c_str());
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
        float array[4] = { _defaultAmbientLight, _defaultAmbientLight,
            _defaultAmbientLight, 1.0f };
        SetShaderValue(_shader, ambientLoc, array, SHADER_UNIFORM_VEC4);

        debugMode = std::make_shared<DebugMode>(_assetsRoot, _shader, _gridSize);
        _hudMode = std::make_unique<HudMode>(_assetsRoot, _gridSize);
        _escapeMenu = std::make_shared<EscapeMenu>(_assetsRoot, *this);
        _window.ToggleFullscreen();

        // Create lights
        float lightHeight = _gridSize * 10.0f;
        float extremity = _gridSize * 30;
        _lights[0] = CreateLight(LIGHT_POINT, (Vector3){ extremity, lightHeight, extremity }, Vector3Zero(), SUN_COLOR, _shader);
        _lights[1] = CreateLight(LIGHT_POINT, (Vector3){ 0, lightHeight, extremity }, Vector3Zero(), MOON_COLOR, _shader);
        // _lights[2] = CreateLight(LIGHT_POINT, (Vector3){ extremity, lightHeight, 0 }, Vector3Zero(), GREEN, _shader);
        // _lights[3] = CreateLight(LIGHT_POINT, (Vector3){ 0, lightHeight, 0 }, Vector3Zero(), BLUE, _shader);

        // -- Camera --
        //* Front of the scene
        _defaultCameraPosition = raylib::Vector3(4.8, 2.5, 20) * _gridSize;
        _defaultCameraTarget = raylib::Vector3(4.8, 2.2, 13.1) * _gridSize;
        //* Menu
        _startPos = getStartPos();
        _startTarget = getStartTarget();
        _camera.SetPosition(_startPos);
        _camera.SetTarget(_startTarget);

        // DisableCursor();

        // Load floor texture
        _floorTexture = raylib::Texture2D(_assetsRoot + TILE_TEXTURE_PATH);
        _floorMesh = GenMeshPlane(_gridSize, _gridSize, 1, 1);
        _floorMaterial = LoadMaterialDefault();
        _floorMaterial.maps[MATERIAL_MAP_DIFFUSE].texture = _floorTexture;
        _floorMaterial.shader = _shader;

        _hitGridTexture = raylib::Texture2D(_assetsRoot + "textures/pokemon_hit_tile.png");
        _hitGridMaterial = LoadMaterialDefault();
        _hitGridMaterial.maps[MATERIAL_MAP_DIFFUSE].texture = _hitGridTexture;

        _arena = raylib::Model(_assetsRoot + ARENA_MODEL_PATH);
        for (int i = 0; i < _arena.materialCount; i++)
            _arena.materials[i].shader = _shader;

        // -- Rocks --
        _rockTextures.push_back(_assetsRoot + "textures/pokeball/poke_ball.png");
        _rockTextures.push_back(_assetsRoot + "textures/pokeball/great_ball.png");
        _rockTextures.push_back(_assetsRoot + "textures/pokeball/ultra_ball.png");
        _rockTextures.push_back(_assetsRoot + "textures/pokeball/premier_ball.png");
        _rockTextures.push_back(_assetsRoot + "textures/pokeball/luxury_ball.png");
        _rockTextures.push_back(_assetsRoot + "textures/pokeball/master_ball.png");
        _rockAnimations = raylib::ModelAnimation::Load(_assetsRoot + POKEBALL_MODEL_PATH);
        _rockModel.materials[1].shader = _shader;

        // -- Food --
        _foodModel.materials[1].shader = _shader;
        _listTypes = {"grass", "fire", "water",
                      "steel", "dragon", "electric",
                      "bug", "psychic", "ground",
                      "dark", "fight", "fairy",
                      "ice", "normal", "poison",
                      "rock", "ghost", "fly",
                      "eevee", "mustebee"};
        _listTypesColors = {
            (Color){107, 190, 48, 255}, (Color){231, 59, 12, 255}, (Color){48, 144, 241, 255},
            (Color){179, 179, 194, 255}, (Color){113, 89, 215, 255}, (Color){250, 179, 21, 255},
            (Color){148, 162, 18, 255}, (Color){234, 67, 125, 255}, (Color){203, 171, 82, 255},
            (Color){79, 57, 43, 255}, (Color){126, 50, 26, 255}, (Color){239, 172, 241, 255},
            (Color){126, 218, 244, 255}, (Color){197, 191, 180, 255}, (Color){146, 66, 144, 255},
            (Color){181, 161, 88, 255}, (Color){89, 92, 169, 255}, (Color){138, 159, 239, 255},
            raylib::Color::White(), raylib::Color::Orange(),
        };
        _listTypesCustom.push_back("");
        _listTypesColorsCustom.push_back(raylib::Color::White());

        // -- Eggs --
        _eggModelAnimations = raylib::ModelAnimation::Load(_assetsRoot + EGG_MODEL_PATH);

        _moon.materials[1].shader = _shader;

        raylib::Color baseColor = raylib::Color(0x5D76F1);
        for (int i = 0; i < _tv.materialCount; i++) {
            _tv.materials[i].shader = _shader;
            raylib::Color randomColor = raylib::Color(Utils::random(0, 255),
                Utils::random(0, 255), Utils::random(0, 255), 255);
            _tv.materials[i].maps[MATERIAL_MAP_DIFFUSE].color = randomColor;
        }
        for (int i = 0; i < 3; i++)
            _tv.materials[i].maps[MATERIAL_MAP_DIFFUSE].color = baseColor;
        _tv.materials[7].maps[MATERIAL_MAP_DIFFUSE].color = baseColor;

        _arenaAltitudeScale = -(1. / 13.);
        _arenaScale = _gridSize;
        getArenaOffset = [](size_t tileCount, float gridSize) -> float {
            float correction = tileCount % 2 == 0 ? gridSize / 2 : 0;
            return tileCount / 2 * gridSize - correction;
        };

        // Music
        InitAudioDevice();
        _mainTheme = raylib::Music(_assetsRoot + MAIN_THEME_PATH);
        _mainTheme.Play();
        _mainTheme.SetLooping(true);
        float randNum = Utils::random(80, 120) / 100.;
        _mainTheme.SetPitch(0.8 + 0.1 * randNum);
        _mainTheme.SetVolume(0.07);

        // Pantheon
        _pantheon = std::make_unique<Pantheon>(assetsRoot, *this);

        // Menu gif
        std::string menuPath = "menu/";
        _isMenuDay = Utils::random(0, 1) == 0;
        menuPath += _isMenuDay ? "day/" : "dawn/";
        _menuIntroGif = std::make_unique<raylib::Gif>(
            _assetsRoot + menuPath + "frames_intro", false, 0, _isMenuDay ? 1.1 : 1.0);
        _menuIntroGif->reset();
        _menuGif = std::make_unique<raylib::Gif>(
            _assetsRoot + menuPath + "frames_main", true, 1, _isMenuDay ? 1.1 : 1.0);

        // Broadcast gif
        _broadcastGif.reset();
    }
}
