#pragma once
#include <cstring>
#include "Constants.h"
#include "Battleship.h"

class Player
{
private:

    int GetShipId(string searchedConfig);

    void ReadConfigFile();

public:
    string Name;

    int sixTileShips = 0;
    int fourTileShips = 0;
    int threeTileShips = 0;
    int twoTileShips = 0;

    Battleship battleships[SHIPS_AMOUNT];

    int ShipsBoard[BOARD_HEIGHT][BOARD_WIDTH] = { 0 };

    int HitsBoard[BOARD_HEIGHT][BOARD_WIDTH] = { 0 };

    void PlayerStart();

    bool PlayerTurn(Player& enemy);

    int GetHitShipId(Battleship enemyBattleships[], Point hitPoint);

    bool GetVesselCount();

    void GetSunkVesselsCount();
};