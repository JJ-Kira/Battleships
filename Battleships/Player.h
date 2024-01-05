#pragma once
#include <cstring>
#include "Constants.h"
#include "Battleship.h"

class Player
{
protected:
    int sixTileShips = 0;
    int fourTileShips = 0;
    int threeTileShips = 0;
    int twoTileShips = 0;

    Battleship battleships[SHIPS_AMOUNT];

private:

    int GetShipId(string searchedConfig);

    int GetHitShipId(Battleship enemyBattleships[], Point hitPoint);

    void ReadConfigFile();

public:
    string Name;

    int ShipsBoard[BOARD_HEIGHT][BOARD_WIDTH] = { 0 };

    int HitsBoard[BOARD_HEIGHT][BOARD_WIDTH] = { 0 };

    void PlayerStart();

    bool PlayerTurn(Player& enemy);

    bool GetVesselCount();

    void GetSunkVesselsCount();
};