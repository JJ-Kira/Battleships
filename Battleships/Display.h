#pragma once
#include <iostream>
#include "Constants.h"

using namespace std;

// Display one board in format of 10x10 matrix
void DisplayBoard(int playerShipBoard[][BOARD_WIDTH]);

// Display two board in format of 10x10 matrix, side by side
void Display2Boards(int playerShipBoard[][BOARD_WIDTH], int playerHitBoard[][BOARD_WIDTH]);

void ClearConsole();