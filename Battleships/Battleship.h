#pragma once
#include <iostream>
#include <cstring>
#include <string>
#include <fstream>
#include "Constants.h"
using namespace std;

int TransformBoardChar(char character);

struct Point {
    int x = -2, y = -2;
};

class Battleship {
public:
    char positionLetter = ' ', directionLetter = ' ';
    int positionNumber = -1, length = 0;

    // Ship coordinates on player's board
    Point shipsCoordinates[MAX_SHIP_SIZE] = {};
    // Ship coordinates that were hit
    Point hitsCoordinates[MAX_SHIP_SIZE] = {};

    void PrintConfig();
    
    bool CheckConfig(int playerShipBoard[][BOARD_WIDTH], int sixTileShips, int fourTileShips, int threeTileShips, int twoTileShips);

    void InputBattleshipConfig(int& sixTileShips, int& fourTileShips, int& threeTileShips, int& twoTileShips);

    void WriteBattleshipCoordinates();

    void EraseBattleshipCoordinates();

    void CorrectConfig(int playerShipBoard[][BOARD_WIDTH], int& sixTileShips, int& fourTileShips, int& threeTileShips, int& twoTileShips);

    bool IsColliding(int playerShipBoard[][BOARD_WIDTH]);

    bool IsShipSunk();

    void AddHitCollision(int playerHitBoard[][BOARD_WIDTH]);

    void AddShipCollision(int playerShipBoard[][BOARD_WIDTH]);

    void EraseShipCollision(int playerShipBoard[][BOARD_WIDTH]);

    void AddToHitBoard(int playerHitBoard[][BOARD_WIDTH]);

    void AddToShipBoard(int playerShipBoard[][BOARD_WIDTH]);

    void EraseFromShipBoard(int playerShipBoard[][BOARD_WIDTH]);
};