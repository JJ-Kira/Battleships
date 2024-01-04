#pragma once
#include <iostream>
#include <cstring>
#include <string>
#include <fstream>
#include "Constants.h"
using namespace std;

// Transform A to 0, B to 1 ....
int TransformBoardChar(char character);

struct Point {
    int x = -2, y = -2;
};

class Battleship {
public:
    char positionLetter = ' ', directionLetter = ' ';
    int positionNumber = -1, length = 0;

    // Ship coordinates on player's board
    Point shipCoordinates[MAX_SHIP_SIZE] = {};
    // Ship coordinates that were hit
    Point hitCoordinates[MAX_SHIP_SIZE] = {};

    // Print ship configuration in format A1 R L
    void PrintConfig();
    
    // Check config correctness
    bool CheckConfig(int playerShipBoard[][BOARD_WIDTH], int sixTileShips, int fourTileShips, int threeTileShips, int twoTileShips);

    // Input battleship configuration in format A1 R L
    void InputBattleshipConfig(int& sixTileShips, int& fourTileShips, int& threeTileShips, int& twoTileShips);

    // Write battleship coordinates based on battleship configuration
    void WriteBattleshipCoordinates();

    // Erase battleship coordinates
    void EraseBattleshipCoordinates();

    // Correct ship configuration
    void CorrectConfig(int playerShipBoard[][BOARD_WIDTH], int& sixTileShips, int& fourTileShips, int& threeTileShips, int& twoTileShips);

    // Check if battleship coordinates collide with other battleship coordinates
    bool IsColliding(int playerShipBoard[][BOARD_WIDTH]);

    // Check if all battleship coordinates were hit
    bool IsShipSunk();

    // Add collision area to hit board
    void AddHitCollision(int playerHitBoard[][BOARD_WIDTH]);

    // Add collision area to ship board
    void AddShipCollision(int playerShipBoard[][BOARD_WIDTH]);

    // Erase collision area
    void EraseShipCollision(int playerShipBoard[][BOARD_WIDTH]);

    // Add ship's image to hit board
    void AddToHitBoard(int playerHitBoard[][BOARD_WIDTH]);

    // Add ship's image to ship board
    void AddToShipBoard(int playerShipBoard[][BOARD_WIDTH]);

    // Erase ship's image
    void EraseFromShipBoard(int playerShipBoard[][BOARD_WIDTH]);
};