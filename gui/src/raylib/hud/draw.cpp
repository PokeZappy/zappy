/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** draw.cpp
*/

#include "Raylib.hpp"
#include "HudMode.hpp"

namespace Zappy {
     void HudMode::drawBackground(const World &world, size_t graphicPlayerCount, size_t graphicEggCount) {
        raylib::Rectangle _backgroundSrc(0, 0, _backgroundHudTexture.width, _backgroundHudTexture.height);
        raylib::Rectangle _backgroundDest(0, GUI_HEIGHT - 200, GUI_WIDTH, 200);

        raylib::Rectangle _attackSrc(0, 0, _attackHudTexture.width, _attackHudTexture.height);
        raylib::Rectangle _attackDest(GUI_WIDTH - 700, GUI_HEIGHT - 200, 700, 200);


        if (_targetedPlayer != nullptr)
            drawLegend();
        _backgroundHudTexture.Draw(_backgroundSrc, _backgroundDest);

        if (_chat)
            drawChat();
        else
            _black120.DrawText("Press 'T' to open chat", 13, GUI_HEIGHT - 241, 25);

        drawEntityCount(graphicPlayerCount, graphicEggCount, world.getPlayers().size(), world.getEggs().size(), 1657, 156);
        drawShell(world.getShellCommands());
        Inventory sumResources;
        const std::vector<std::vector<Tile>> &tiles = world.getTiles();
        for (size_t x = 0; x < tiles.size(); x++) {
            for (size_t y = 0; y < tiles[x].size(); y++) {
                sumResources += tiles[x][y].getInventory();
            }
        }
        drawInventory(sumResources, 1657, 0, "Total");

        if (_selectedTile != nullptr) {
            drawInventory(_selectedTile->getInventory(), 0, GUI_HEIGHT - 200, "Tile " + std::to_string(_selectedTile->getX()) + " " + std::to_string(_selectedTile->getY()));
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
                // setSelectedPlayerToTarget();
                _selectedPlayer = _targetedPlayer;
            } else if (!_selectedPlayers.empty()){
                _selectedPlayer = _selectedPlayers[0];
            }
        } else {
            verifyPlayerPosition();
        }
        if (_selectedPlayer != nullptr) {
            drawPokemons();
            drawInventory(_selectedPlayer->worldPlayer->getInventory(), 900, GUI_HEIGHT - 200, "Pokemon");
            _attackHudTexture.Draw(_attackSrc, _attackDest);
            drawAttacks();
        } else if (_selectedTile == nullptr) {
            _white.DrawText("Sélectionner une case à afficher (avec la souris)", 491, GUI_HEIGHT - 120, 45);
        } else {
            _white.DrawText("Aucun pokemon trouvé sur cette case", 644, GUI_HEIGHT - 120, 45);
        }
    }

    void HudMode::drawEntityCount(size_t graphicPlayerCount, size_t graphicEggCount, size_t worldPlayerCount, size_t worldEggCount, int x, int y) {
        raylib::Rectangle _tileSrc(0, 0, _inventoryHudTexture.width, _inventoryHudTexture.height);
        raylib::Rectangle _tileDest(x, y, 265, 200);

        // 1657; 156;

        _inventoryHudTexture.Draw(_tileSrc, _tileDest);
        _playerTexture.Draw(x + 35, y + 50);
        _eggTexture.Draw(x + 32, y + 122);
        _white.DrawText("World: " + std::to_string(worldPlayerCount), x + 80, y + 58, 20);
        _white.DrawText("Graphic: " + std::to_string(graphicPlayerCount), x + 80, y + 78, 20);

        _white.DrawText("World: " + std::to_string(worldEggCount), x + 80, y + 120, 20);
        _white.DrawText("Graphic: " + std::to_string(graphicEggCount), x + 80, y + 140, 20);
    }

    void HudMode::drawShell(const std::vector<ShellCommand> &shellCommands)
    {
        int defaultOffsetX = 13;
        int defaultOffsetY = GUI_HEIGHT - 300;

        unsigned char alpha = 255;
        raylib::Color textColor = raylib::Color::White();

        size_t size = _chat ? shellCommands.size() : 5;
        if (size > shellCommands.size())
            size = shellCommands.size();

        for (size_t i = 0; i < size; i++) {
            auto &command = shellCommands[i];
            if (command.getEntity() != nullptr) {
                drawType(command.getEntity()->getTeam().getName(), defaultOffsetX, defaultOffsetY + 5);
            }
            textColor.a = alpha;
            alpha -= 4;
            textColor.DrawText(command.text, defaultOffsetX + 75, defaultOffsetY + 10, 20);
            defaultOffsetY -= 35;
        }
    }

    void HudMode::drawAttacks() {
        _white.DrawText("Teleport (1)", 1288, GUI_HEIGHT - 156, 40);
        if (_targetedPlayer == _selectedPlayer)
            _white.DrawText("Unfollow (2)", 1607, GUI_HEIGHT - 156, 40);
        else
            _white.DrawText("Follow (2)", 1607, GUI_HEIGHT - 156, 40);
        _white.DrawText("Heal (3)", 1288, GUI_HEIGHT - 95, 40);
        _white.DrawText("Kill (4)", 1607, GUI_HEIGHT - 95, 40);
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
        raylib::Rectangle _inventoryDest(topX, topY, 265, 200);
        raylib::Rectangle ballSrc(0, 0, _pokeBallTexture.width, _pokeBallTexture.height);

        _inventoryHudTexture.Draw(_inventorySrc, _inventoryDest);
        _white.DrawText(title, topX + 32, topY + 40, 20);

        int xLeftBalls = 28;
        int xLeftText = xLeftBalls + 35;
        int xRightBalls = 130;
        int xRightText = xRightBalls + 35;

        _pokeBallTexture.Draw(ballSrc, raylib::Rectangle(topX + xLeftBalls, topY + 71, 30, 30));
        // _pokeBallTexture.Draw(x + 45, GUI_HEIGHT - 129);
        _white.DrawText(std::to_string(inventory.getItem(1)), topX + xLeftText, topY + 76, 20);

        _superBallTexture.Draw(ballSrc, raylib::Rectangle(topX + xLeftBalls, topY + 102, 30, 30));
        // _superBallTexture.Draw(x + 45, GUI_HEIGHT - 98);
        _white.DrawText(std::to_string(inventory.getItem(2)), topX + xLeftText, topY + 107, 20);

        _hyperBallTexture.Draw(ballSrc, raylib::Rectangle(topX + xLeftBalls, topY + 133, 30, 30));
        // _hyperBallTexture.Draw(x + 45, GUI_HEIGHT - 67);
        _white.DrawText(std::to_string(inventory.getItem(3)), topX + xLeftText, topY + 138, 20);

        _foodTexture.Draw(ballSrc, raylib::Rectangle(topX + xRightBalls, topY + 40, 30, 30));
        // _foodTexture.Draw(x + 149, GUI_HEIGHT - 160);
        _white.DrawText(std::to_string(inventory.getItem(0)), topX + xRightText, topY + 45, 20);

        _honorBallTexture.Draw(ballSrc, raylib::Rectangle(topX + xRightBalls, topY + 71, 30, 30));
        // _honorBallTexture.Draw(x + 149, GUI_HEIGHT - 129);
        _white.DrawText(std::to_string(inventory.getItem(4)), topX + xRightText, topY + 76, 20);

        _luxeBallTexture.Draw(ballSrc, raylib::Rectangle(topX + xRightBalls, topY + 102, 30, 30));
        // _luxeBallTexture.Draw(x + 149, GUI_HEIGHT - 98);
        _white.DrawText(std::to_string(inventory.getItem(5)), topX + xRightText, topY + 107, 20);

        _masterBallTexture.Draw(ballSrc, raylib::Rectangle(topX + xRightBalls, topY + 133, 30, 30));
        // _masterBallTexture.Draw(x + 149, GUI_HEIGHT - 67);
        _white.DrawText(std::to_string(inventory.getItem(6)), topX + xRightText, topY + 138, 20);
    }

    void HudMode::drawPokemons() {

        int pokemon_drawn = 1;

        if (_targetedPlayer != nullptr)
            drawPokemon(_targetedPlayer, GUI_HEIGHT - 171, _green);

        for (size_t i = _scrollIndex; i < _scrollIndex + 3 && i < _selectedPlayers.size(); i++) {
            drawPokemon(_selectedPlayers[i], GUI_HEIGHT - 171 + (pokemon_drawn++ * 43), _white);
        }
    }

    void HudMode::drawLegend() {
        raylib::Rectangle _tileSrc(0, 0, _inventoryHudTexture.width, _inventoryHudTexture.height);
        raylib::Rectangle _tileDest(612, GUI_HEIGHT - 275, 265, 200);

        _inventoryHudTexture.Draw(_tileSrc, _tileDest);
        _green.DrawText(">", 648, GUI_HEIGHT - 241, 30);
        _white.DrawText("Followed Pokemon", 683, GUI_HEIGHT - 233, 18);
    }

    void HudMode::drawPokemon(std::shared_ptr<PlayerRaylib> pokemon, int y, raylib::Color colorArrow) {
        if (pokemon == _selectedPlayer || pokemon == _targetedPlayer) {
            colorArrow.DrawText(">", 286, y, 30);
        }
        _white.DrawText(std::to_string(pokemon->worldPlayer->getId()), 336, y, 25);
        _white.DrawText(pokemon->infos.displayName, 452, y, 25);
        _white.DrawText("N." + std::to_string(pokemon->worldPlayer->getLevel()), 645, y, 25);

        drawType(pokemon->worldPlayer->getTeam().getName(), 706, y);

        if (pokemon->worldPlayer->getIncantationState() == Incantation::INCANTING) {
            _encantingTexture.Draw(raylib::Rectangle(0, 0, _encantingTexture.width, _encantingTexture.height), raylib::Rectangle(855, y, 22, 29));
        } else {
            _notEncantingTexture.Draw(raylib::Rectangle(0, 0, _notEncantingTexture.width, _notEncantingTexture.height), raylib::Rectangle(855, y, 22, 29));
        }
    }

    void HudMode::drawChat()
    {
        std::chrono::duration<double> elapsed_seconds = std::chrono::steady_clock::now() - _cursorClock;

        raylib::Color(0, 0, 0, 60).DrawRectangle((Vector2) {0, 10}, (Vector2) {554, GUI_HEIGHT - 280});
        _black120.DrawRectangle((Vector2) {0, GUI_HEIGHT - 248}, (Vector2) {554, 41});
        int decal = _inputString.size() - 30;
        int indexSubstr = decal > 0 ? decal : 0;
        float blinkTime = 0.7;
        char cursor = '\0';
        if (elapsed_seconds.count() < blinkTime) {
            cursor = '|';
        } else if (elapsed_seconds.count() > blinkTime * 2) {
            _cursorClock = std::chrono::steady_clock::now();
        }
        _white.DrawText("> " + _inputString.substr(indexSubstr, _inputString.size()) + cursor, 13, GUI_HEIGHT - 243, 30);
    }

    void HudMode::drawType(std::string type, int x, int y) {
        raylib::Rectangle src;
        raylib::Rectangle dest(x, y, 57, 25);
        if (type == "bug") {
            src = raylib::Rectangle(0, 14, _typesTexture.width, 14);
        } else if (type == "dark") {
            src = raylib::Rectangle(0, 28, _typesTexture.width, 14);
        } else if (type == "dragon") {
            src = raylib::Rectangle(0, 42, _typesTexture.width, 14);
        } else if (type == "electric") {
            src = raylib::Rectangle(0, 56, _typesTexture.width, 14);
        } else if (type == "fairy") {
            src = raylib::Rectangle(0, 70, _typesTexture.width, 14);
        } else if (type == "fight") {
            src = raylib::Rectangle(0, 84, _typesTexture.width, 14);
        } else if (type == "fire") {
            src = raylib::Rectangle(0, 98, _typesTexture.width, 14);
        } else if (type == "fly") {
            src = raylib::Rectangle(0, 112, _typesTexture.width, 14);
        } else if (type == "ghost") {
            src = raylib::Rectangle(0, 126, _typesTexture.width, 14);
        } else if (type == "grass") {
            src = raylib::Rectangle(0, 140, _typesTexture.width, 14);
        } else if (type == "ground") {
            src = raylib::Rectangle(0, 154, _typesTexture.width, 14);
        } else if (type == "ice") {
            src = raylib::Rectangle(0, 168, _typesTexture.width, 14);
        } else if (type == "normal") {
            src = raylib::Rectangle(0, 182, _typesTexture.width, 14);
        } else if (type == "poison") {
            src = raylib::Rectangle(0, 196, _typesTexture.width, 14);
        } else if (type == "psychic") {
            src = raylib::Rectangle(0, 210, _typesTexture.width, 14);
        } else if (type == "rock") {
            src = raylib::Rectangle(0, 224, _typesTexture.width, 14);
        } else if (type == "steel") {
            src = raylib::Rectangle(0, 238, _typesTexture.width, 14);
        } else if (type == "water") {
            src = raylib::Rectangle(0, 252, _typesTexture.width, 14);
        } else {
            _white.DrawText(type, x, y, 25);
        }
        _typesTexture.Draw(src, dest);
    }
}
