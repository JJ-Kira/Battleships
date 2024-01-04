#pragma once
#include <cstring>
#include "Constants.h"
#include "Battleship.h"

struct Player
{
    string Name;

    // Specific player's ships amount
    int sixTileShips = 0;
    int fourTileShips = 0;
    int threeTileShips = 0;
    int twoTileShips = 0;

    // Player's ship board
    int ShipBoard[BOARD_HEIGHT][BOARD_WIDTH] = { 0 };
    // Player's hit board (board with successful hits of the enemy ships)
    int HitBoard[BOARD_HEIGHT][BOARD_WIDTH] = { 0 };

    // Player's battleships
    Battleship battleships[MAX_SHIPS_AMOUNT];

    // Based on given config(A1 R L) this method finds the ship's index in battleships[]
    int GetShipIdx(string searchedConfig);
    
    // Based on given config(A1 R L) this method finds the ship's index in enemy's battleships[]
    int GetHitShipIdx(Battleship enemyBattleships[], Point hitPoint);

    // Transfers configuration data from file to certain program's structures
    void GetConfigFromFile();

    // Player input or loading from file
    void PlayerStart();

    // Player turn
    bool PlayerTurn(Player& enemy);

};