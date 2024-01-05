#pragma once
#include <iostream>
#include <cstring>
#include <string>
#include <fstream>
#include "Player.h"
#include "Display.h"
#include "ArtificialEnemy.h"

using namespace std;

class BattleshipsManager {
private:
    Player player1, player2;
    ArtificialEnemy enemy;
    int mode;
public:
    BattleshipsManager(string name1, string name2, int numberOfPlayers);
    void LetTheGameBegin();
    bool NextTurn(Player &activePlayer, Player &activeEnemy);
};

