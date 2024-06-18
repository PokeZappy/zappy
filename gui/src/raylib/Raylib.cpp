/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** Raylib.cpp
*/

#include "Raylib.hpp"

namespace Zappy
{
    Raylib::Raylib() : _window(GUI_WIDTH, GUI_HEIGHT, "Zappy"), _camera(Vector3{(10.0F), (100.0F), (10.0F)}, Vector3{(0.0F), (0.0F), (0.0F)}, Vector3{(0.0F), (1.0F), (0.0F)}, 45.0f)
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
        _floorMesh = GenMeshPlane(GRID_SIZE, GRID_SIZE, 1, 1);
        _floorMaterial = LoadMaterialDefault();
        _floorMaterial.maps[MATERIAL_MAP_DIFFUSE].texture = _floorTexture;

        _tv = raylib::Model("assets/models/nintendo_game_boy.glb");
        _pokeCenter = raylib::Model("assets/models/pokecenter.glb");
        listTypes = {"grass", "fire", "water"};
    }

    void Raylib::render(const World &world)
    {
        (void)world;
        raylib::Color textColor = raylib::Color::Black();
        _window.BeginDrawing();
        {
            _window.ClearBackground(raylib::Color::SkyBlue());
            _window.DrawFPS();
            // 3D scene

            _camera.BeginMode();
            for (int x = 0; x < 10; x++)
            {
                for (int z = 0; z < 10; z++)
                {
                    DrawMesh(_floorMesh, _floorMaterial, MatrixTranslate(x * GRID_SIZE, 0.0f, z * GRID_SIZE));
                }
            }

            for (auto &player : _players)
            {
                player.draw();
            }

            _tv.Draw(raylib::Vector3(_mapX / 2 * GRID_SIZE - 50, 80, -GRID_SIZE * 4), 2000);

            _camera.EndMode();
            // end of 3D scene
            textColor.DrawText(raylib::Vector3(_camera.GetPosition()).ToString(), 50, 50, 25);
            textColor.DrawText(raylib::Vector3(_camera.GetTarget()).ToString(), 50, 80, 25);
        }
        _window.EndDrawing();
    }

    void Raylib::drawTiles(const std::vector<std::vector<Tile>> &tiles)
    {
        return;
    }

    void Raylib::drawEntity(const std::shared_ptr<IEntity> entity)
    {
        return;
    }

    bool Raylib::containsPlayer(std::shared_ptr<Player> player)
    {
        for (const auto &playerRaylib : _players)
        {
            if (playerRaylib.worldPlayer == player)
            {
                return true;
            }
        }
        return false;
    }

    PokemonInfo Raylib::parsePokemon(libconfig::Setting &pokemon)
    {
        PokemonInfo pkInfo = PokemonInfo();

        try
        {
            std::cout << "j'essaie" << std::endl;
            std::string pokeName = pokemon["name"];
            std::string pokeId = pokemon["id"];
            int stage = pokemon["stage"];
            pkInfo.displayName = pokeName;
            pkInfo.id = pokeId;
            pkInfo.stage = stage;
            libconfig::Setting &evos = pokemon["evolutions"];
            for (int i = 0; i < evos.getLength(); i++)
            {
                pkInfo.evolutions.push_back(parsePokemon(evos[i]));
            }
        }
        catch (libconfig::SettingNotFoundException &ex)
        {
            std::cerr << ex.what() << std::endl;
            // return (false);
        }
        catch (libconfig::SettingTypeException &ex)
        {
            std::cerr << ex.what() << std::endl;
            // return (false);
        }

        return pkInfo;
    }

    PokemonInfo Raylib::getPokemon(std::string team)
    {
        std::string t = team;

        if (std::find(listTypes.begin(), listTypes.end(), team) == listTypes.end())
        {
            // pas trouvé
            t = listTypes[Utils::random(0, listTypes.size() - 1)];
        }
        try
        {
            std::cout << "team utilise : " << t << std::endl;
            libconfig::Setting &root = _configuration.getRoot();
            libconfig::Setting &types = root["types"];
            libconfig::Setting &pokemons = types[t.c_str()];
            return parsePokemon(pokemons[Utils::random(0, pokemons.getLength() - 1)]);
        }
        catch (libconfig::SettingNotFoundException &ex)
        {
            std::cerr << ex.what() << std::endl;
            // return (false);
        }
        catch (libconfig::SettingTypeException &ex)
        {
            std::cerr << ex.what() << std::endl;
            // return (false);
        }
        return PokemonInfo();
    }

    void Raylib::testEvolution(void)
    {
         for (auto &graphicPlayer : _players)
        {
            PokemonInfo &infos = graphicPlayer.infos;
            bool isAbleToEvolve = false;
            int maxStage = 1;
            if (infos.evolutions.empty())
                continue;
            switch (infos.stage)
            {
            case 1:
                 if (infos.evolutions[0].evolutions.empty())
                    maxStage = 2;
                else
                    maxStage = 3;
                switch (maxStage) {
                    case 2:
                        isAbleToEvolve = (graphicPlayer.worldPlayer->getLevel() >= 4); break;
                    case 3:
                        isAbleToEvolve = (graphicPlayer.worldPlayer->getLevel() >= 3); break;
                    default: break;
            } break;
            case 2:
                if (infos.evolutions.empty()) break;
                isAbleToEvolve = (graphicPlayer.worldPlayer->getLevel() >= 6);
                break;
            }
            if (isAbleToEvolve) {
                PokemonInfo pickedEvolution = infos.evolutions[Utils::random(0, infos.evolutions.size() - 1)];
                pickedEvolution.shiny = infos.shiny;
                infos = pickedEvolution;
                graphicPlayer.loadTextureAndModel();
            }
        }
    }

    void Raylib::update(const World &world)
    {
        if (IsKeyDown(KEY_SPACE))
        {
            _camera.position.y += 1;
            _camera.target.y += 1;
        }
        if (IsKeyDown(KEY_LEFT_SHIFT))
        {
            _camera.position.y -= 1;
            _camera.target.y -= 1;
        }
        _camera.Update(CAMERA_FIRST_PERSON);
        for (const auto &player : world.getPlayers())
        {
            if (!containsPlayer(player))
            {
                PokemonInfo pokemon = getPokemon(player.get()->getTeam().getName());
                pokemon.shiny = Utils::random(0, 20) == 6;
                // pokemon.shiny = true;
                _players.push_back(PlayerRaylib(player, pokemon));
            }
        }
        testEvolution();
    }

    bool Raylib::isOpen()
    {
        return (!_window.ShouldClose());
    }
}
