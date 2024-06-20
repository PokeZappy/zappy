/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** pokemon.cpp
*/

#include "Raylib.hpp"

namespace Zappy {
    PokemonInfo Raylib::parsePokemon(libconfig::Setting &pokemon)
    {
        PokemonInfo pkInfo = PokemonInfo();

        try
        {
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
            PokemonInfo &infos = graphicPlayer->infos;
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
                        isAbleToEvolve = (graphicPlayer->worldPlayer->getLevel() >= 4); break;
                    case 3:
                        isAbleToEvolve = (graphicPlayer->worldPlayer->getLevel() >= 3); break;
                    default: break;
            } break;
            case 2:
                if (infos.evolutions.empty()) break;
                isAbleToEvolve = (graphicPlayer->worldPlayer->getLevel() >= 6);
                break;
            }
            if (isAbleToEvolve) {
                PokemonInfo pickedEvolution = infos.evolutions[Utils::random(0, infos.evolutions.size() - 1)];
                pickedEvolution.shiny = infos.shiny;
                infos = pickedEvolution;
                graphicPlayer->loadTextureAndModel();
            }
        }
    }
}
