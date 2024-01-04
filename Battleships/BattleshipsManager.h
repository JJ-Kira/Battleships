#pragma once
#include <iostream>
#include <cstring>
#include <string>
#include <fstream>
#include "Player.h"
#include "Display.h"

using namespace std;

class BattleshipsManager {
private:
    Player player1, player2;
public:
    BattleshipsManager(string name1, string name2);
    void LetTheGameBegin();
    bool NextTurn(Player activePlayer, Player activeEnemy);
};

