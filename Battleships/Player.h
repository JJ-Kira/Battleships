#pragma once
#include <cstring>
#include "Constants.h"
#include "Battleship.h"

class Player
{
private:
    int sixTileShips = 0;
    int fourTileShips = 0;
    int threeTileShips = 0;
    int twoTileShips = 0;

    // Player's battleships
    Battleship battleships[SHIPS_AMOUNT];

    // Based on given config(A1 R L) this method finds the ship's index in battleships[]
    int GetShipId(string searchedConfig);

    // Based on given config(A1 R L) this method finds the ship's index in enemy's battleships[]
    int GetHitShipId(Battleship enemyBattleships[], Point hitPoint);

    // Transfers configuration data from file to certain program's structures
    void ReadConfigFile();

public:
    string Name;

    // Player's ship board
    int ShipBoard[BOARD_HEIGHT][BOARD_WIDTH] = { 0 };
    // Player's hit board (board with successful hits of the enemy ships)
    int HitBoard[BOARD_HEIGHT][BOARD_WIDTH] = { 0 };

    // Player input or loading from file
    void PlayerStart();

    // Player turn
    bool PlayerTurn(Player& enemy);

    bool GetShipCount();
};