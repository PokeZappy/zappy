/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** draw.cpp
*/

#include "Raylib.hpp"
#include "HudMode.hpp"
#include "UtilsRaylib.hpp"

namespace Zappy {
     void HudMode::drawBackground(const World &world, size_t graphicPlayerCount, size_t graphicEggCount) {
        raylib::Rectangle _backgroundSrc(0, 0, _backgroundHudTexture.width, _backgroundHudTexture.height);
        raylib::Rectangle _backgroundDest(0, Layout::bottom(GUI_HEIGHT - 200),
            Layout::w(), Layout::s(200));

        raylib::Rectangle _attackSrc(0, 0, _attackHudTexture.width, _attackHudTexture.height);
        raylib::Rectangle _attackDest(Layout::right(GUI_WIDTH - 700),
            Layout::bottom(GUI_HEIGHT - 200), Layout::s(700), Layout::s(200));


        if (_targetedPlayer != nullptr)
            drawLegend();
        _backgroundHudTexture.Draw(_backgroundSrc, _backgroundDest);

        if (_chat)
            drawChat();
        else
            _black120.DrawText("Appuyez sur 'T' pour ouvrir le chat", Layout::left(13),
                Layout::bottom(GUI_HEIGHT - 241), Layout::s(25));

        drawEntityCount(graphicPlayerCount, graphicEggCount, world.getPlayers().size(),
            world.getEggs().size(), Layout::right(1657), Layout::top(156));
        drawShell(world.getShellCommands());
        Inventory sumResources;
        const std::vector<std::vector<Tile>> &tiles = world.getTiles();
        for (size_t x = 0; x < tiles.size(); x++) {
            for (size_t y = 0; y < tiles[x].size(); y++) {
                sumResources += tiles[x][y].getInventory();
            }
        }
        drawInventory(sumResources, Layout::right(1657), Layout::top(0), "Total");

        if (_selectedTile != nullptr) {
            drawInventory(_selectedTile->getInventory(), Layout::left(0), Layout::bottom(GUI_HEIGHT - 200), "Tile " + std::to_string(_selectedTile->getX()) + " " + std::to_string(_selectedTile->getY()));
        } else {
            // white.DrawText("Séléctionner une tile à afficher", 491, GUI_HEIGHT - 120, 65);
            // return;
        }

        if (_selectedPlayers.empty()) {
            if (_targetedPlayer == nullptr) {
                 _selectedPlayer = nullptr;
                _scrollIndex = 0;
            } else {
                _selectedPlayer = _targetedPlayer;
                _scrollIndex = 0;
            }
        }
        if (_selectedPlayer == nullptr) {
            if (_targetedPlayer != nullptr) {
                _selectedPlayer = _targetedPlayer;
            } else if (!_selectedPlayers.empty()){
                _selectedPlayer = _selectedPlayers[0];
            }
        } else {
            verifyPlayerPosition();
        }
        if (_selectedPlayer != nullptr) {
            drawPokemons();
            drawInventory(_selectedPlayer->worldPlayer->getInventory(), Layout::left(900), Layout::bottom(GUI_HEIGHT - 200), "Pokemon");
            _attackHudTexture.Draw(_attackSrc, _attackDest);
            drawAttacks();
        } else if (_selectedTile == nullptr) {
            _white.DrawText("Sélectionner une case à afficher (avec la souris)", Layout::left(491), Layout::bottom(GUI_HEIGHT - 120), Layout::s(45));
        } else {
            _white.DrawText("Aucun pokemon trouvé sur cette case", Layout::left(644), Layout::bottom(GUI_HEIGHT - 120), Layout::s(45));
        }
    }

    void HudMode::drawEntityCount(size_t graphicPlayerCount, size_t graphicEggCount, size_t worldPlayerCount, size_t worldEggCount, int x, int y) {
        raylib::Rectangle _tileSrc(0, 0, _inventoryHudTexture.width, _inventoryHudTexture.height);
        // x/y arrive already anchored in screen space; the offsets below stay in
        // design space and get scaled here.
        raylib::Rectangle _tileDest(x, y, Layout::s(265), Layout::s(200));

        _inventoryHudTexture.Draw(_tileSrc, _tileDest);
        _playerTexture.Draw(x + Layout::s(35), y + Layout::s(50));
        _eggTexture.Draw(x + Layout::s(32), y + Layout::s(122));
        _white.DrawText("World: " + std::to_string(worldPlayerCount), x + Layout::s(80), y + Layout::s(58), Layout::s(20));
        _white.DrawText("Graphic: " + std::to_string(graphicPlayerCount), x + Layout::s(80), y + Layout::s(78), Layout::s(20));

        _white.DrawText("World: " + std::to_string(worldEggCount), x + Layout::s(80), y + Layout::s(120), Layout::s(20));
        _white.DrawText("Graphic: " + std::to_string(graphicEggCount), x + Layout::s(80), y + Layout::s(140), Layout::s(20));
    }

    void HudMode::drawShell(const std::vector<ShellCommand> &shellCommands)
    {
        int defaultOffsetX = Layout::left(13);
        int defaultOffsetY = Layout::bottom(GUI_HEIGHT - 300);

        unsigned char alpha = 255;
        raylib::Color textColor = raylib::Color::White();

        size_t size = _chat ? shellCommands.size() : 5;
        if (size > shellCommands.size())
            size = shellCommands.size();

        for (size_t i = 0; i < size; i++) {
            auto &command = shellCommands[i];
            if (command.getEntity() != nullptr) {
                drawType(command.getEntity()->getTeam().getName(), defaultOffsetX, defaultOffsetY + Layout::s(5));
            }
            textColor.a = alpha;
            alpha -= 4;
            textColor.DrawText(command.text, defaultOffsetX + Layout::s(75), defaultOffsetY + Layout::s(10), Layout::s(20));
            defaultOffsetY -= Layout::s(35);
        }
    }

    void HudMode::drawAttacks() {
        _white.DrawText("Level Up (1)", Layout::right(1288), Layout::bottom(GUI_HEIGHT - 156), Layout::s(40));
        if (_targetedPlayer == _selectedPlayer)
            _white.DrawText("Unfollow (2)", Layout::right(1607), Layout::bottom(GUI_HEIGHT - 156), Layout::s(40));
        else
            _white.DrawText("Follow (2)", Layout::right(1607), Layout::bottom(GUI_HEIGHT - 156), Layout::s(40));
        _white.DrawText("Heal (3)", Layout::right(1288), Layout::bottom(GUI_HEIGHT - 95), Layout::s(40));
        _white.DrawText("Kill (4)", Layout::right(1607), Layout::bottom(GUI_HEIGHT - 95), Layout::s(40));
    }

    void HudMode::verifyPlayerPosition()
    {
        if (_selectedPlayer == _targetedPlayer)
            return;
        if (std::find(_selectedPlayers.begin(), _selectedPlayers.end(), _selectedPlayer) == _selectedPlayers.end()) {
            if (_scrollIndex >= _selectedPlayers.size())
                _scrollIndex = _selectedPlayers.size() - 1;
            _selectedPlayer = _selectedPlayers[_scrollIndex];
        }
    }

    void HudMode::drawInventory(Inventory inventory, int topX, int topY, std::string title) {
        raylib::Rectangle _inventorySrc(0, 0, _inventoryHudTexture.width, _inventoryHudTexture.height);
        raylib::Rectangle _inventoryDest(topX, topY, Layout::s(265), Layout::s(200));
        raylib::Rectangle ballSrc(0, 0, _pokeBallTexture.width, _pokeBallTexture.height);

        _inventoryHudTexture.Draw(_inventorySrc, _inventoryDest);
        _white.DrawText(title, topX + Layout::s(32), topY + Layout::s(40), Layout::s(20));

        // design-space offsets, scaled at use
        int xLeftBalls = Layout::s(28);
        int xLeftText = xLeftBalls + Layout::s(35);
        int xRightBalls = Layout::s(130);
        int xRightText = xRightBalls + Layout::s(35);
        int ball = Layout::s(30);

        _pokeBallTexture.Draw(ballSrc, raylib::Rectangle(topX + xLeftBalls, topY + Layout::s(71), ball, ball));
        _white.DrawText(std::to_string(inventory.getItem(1)), topX + xLeftText, topY + Layout::s(76), Layout::s(20));

        _superBallTexture.Draw(ballSrc, raylib::Rectangle(topX + xLeftBalls, topY + Layout::s(102), ball, ball));
        _white.DrawText(std::to_string(inventory.getItem(2)), topX + xLeftText, topY + Layout::s(107), Layout::s(20));

        _hyperBallTexture.Draw(ballSrc, raylib::Rectangle(topX + xLeftBalls, topY + Layout::s(133), ball, ball));
        _white.DrawText(std::to_string(inventory.getItem(3)), topX + xLeftText, topY + Layout::s(138), Layout::s(20));

        _foodTexture.Draw(ballSrc, raylib::Rectangle(topX + xRightBalls, topY + Layout::s(40), ball, ball));
        _white.DrawText(std::to_string(inventory.getItem(0)), topX + xRightText, topY + Layout::s(45), Layout::s(20));

        _honorBallTexture.Draw(ballSrc, raylib::Rectangle(topX + xRightBalls, topY + Layout::s(71), ball, ball));
        _white.DrawText(std::to_string(inventory.getItem(4)), topX + xRightText, topY + Layout::s(76), Layout::s(20));

        _luxeBallTexture.Draw(ballSrc, raylib::Rectangle(topX + xRightBalls, topY + Layout::s(102), ball, ball));
        _white.DrawText(std::to_string(inventory.getItem(5)), topX + xRightText, topY + Layout::s(107), Layout::s(20));

        _masterBallTexture.Draw(ballSrc, raylib::Rectangle(topX + xRightBalls, topY + Layout::s(133), ball, ball));
        _white.DrawText(std::to_string(inventory.getItem(6)), topX + xRightText, topY + Layout::s(138), Layout::s(20));
    }

    void HudMode::drawPokemons() {

        int pokemon_drawn = 1;

        if (_targetedPlayer != nullptr)
            drawPokemon(_targetedPlayer, Layout::bottom(GUI_HEIGHT - 171), _green);

        for (size_t i = _scrollIndex; i < _scrollIndex + 3 && i < _selectedPlayers.size(); i++) {
            drawPokemon(_selectedPlayers[i],
                Layout::bottom(GUI_HEIGHT - 171) + (pokemon_drawn++ * Layout::s(43)), _white);
        }
    }

    void HudMode::drawLegend() {
        raylib::Rectangle _tileSrc(0, 0, _inventoryHudTexture.width, _inventoryHudTexture.height);
        raylib::Rectangle _tileDest(Layout::left(612), Layout::bottom(GUI_HEIGHT - 275),
            Layout::s(265), Layout::s(200));

        _inventoryHudTexture.Draw(_tileSrc, _tileDest);
        _green.DrawText(">", Layout::left(648), Layout::bottom(GUI_HEIGHT - 241), Layout::s(30));
        _white.DrawText("Followed Pokemon", Layout::left(683), Layout::bottom(GUI_HEIGHT - 233), Layout::s(18));
    }

    void HudMode::drawPokemon(std::shared_ptr<PlayerRaylib> pokemon, int y, raylib::Color colorArrow) {
        if (pokemon == _selectedPlayer || pokemon == _targetedPlayer) {
            colorArrow.DrawText(">", Layout::left(286), y, Layout::s(30));
        }
        _white.DrawText(std::to_string(pokemon->worldPlayer->getId()), Layout::left(336), y, Layout::s(25));
        _white.DrawText(pokemon->infos.displayName, Layout::left(452), y, Layout::s(25));
        _white.DrawText("N." + std::to_string(pokemon->worldPlayer->getLevel()), Layout::left(645), y, Layout::s(25));

        drawType(pokemon->worldPlayer->getTeam().getName(), Layout::left(706), y);

        if (pokemon->worldPlayer->getIncantationState() == Incantation::INCANTING) {
            _encantingTexture.Draw(raylib::Rectangle(0, 0, _encantingTexture.width, _encantingTexture.height), raylib::Rectangle(Layout::left(855), y, Layout::s(22), Layout::s(29)));
        } else {
            _notEncantingTexture.Draw(raylib::Rectangle(0, 0, _notEncantingTexture.width, _notEncantingTexture.height), raylib::Rectangle(Layout::left(855), y, Layout::s(22), Layout::s(29)));
        }
    }

    void HudMode::drawChat()
    {
        std::chrono::duration<double> elapsed_seconds = std::chrono::steady_clock::now() - _cursorClock;

        raylib::Color(0, 0, 0, 60).DrawRectangle(
            (Vector2) {0, (float)Layout::top(10)},
            (Vector2) {(float)Layout::s(554), (float)(Layout::bottom(GUI_HEIGHT - 280) - Layout::top(10))});
        _black120.DrawRectangle(
            (Vector2) {0, (float)Layout::bottom(GUI_HEIGHT - 248)},
            (Vector2) {(float)Layout::s(554), (float)Layout::s(41)});
        int decal = _inputString.size() - 30;
        int indexSubstr = decal > 0 ? decal : 0;
        float blinkTime = 0.7;
        char cursor = '\0';
        if (elapsed_seconds.count() < blinkTime) {
            cursor = '|';
        } else if (elapsed_seconds.count() > blinkTime * 2) {
            _cursorClock = std::chrono::steady_clock::now();
        }
        _white.DrawText("> " + _inputString.substr(indexSubstr, _inputString.size()) + cursor,
            Layout::left(13), Layout::bottom(GUI_HEIGHT - 243), Layout::s(30));
    }

    void HudMode::drawType(std::string type, int x, int y) {
        raylib::Rectangle src = UtilsRaylib::getTypeRectangle(type);
        raylib::Rectangle dest(x, y, Layout::s(57), Layout::s(25));
        if (src.x == -1) {
            _white.DrawText(type, x, y + Layout::s(7), Layout::s(15));
        } else {
            _typesTexture.Draw(src, dest);
        }
    }
}
