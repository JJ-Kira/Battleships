#pragma once
#include <iostream>
#include "Constants.h"

using namespace std;

void DisplayPlayerBoard(int playerBoard[][BOARD_WIDTH]);

void DisplayPlayerAndEnemyBoards(int playerBoard[][BOARD_WIDTH], int enemyBoard[][BOARD_WIDTH]);

void ClearConsole();