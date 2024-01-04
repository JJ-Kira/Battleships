#pragma once
#include <iostream>
#include "Constants.h"

using namespace std;

// Display one board in format of 10x10 matrix
void DisplayPlayerBoard(int playerBoard[][BOARD_WIDTH]);

// Display two board in format of 10x10 matrix, side by side
void DisplayPlayerAndEnemyBoards(int playerBoard[][BOARD_WIDTH], int enemyBoard[][BOARD_WIDTH]);

void ClearConsole();