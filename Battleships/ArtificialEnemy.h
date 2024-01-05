#pragma once
#include <cstring>
#include "Constants.h"
#include "Battleship.h"
#include "Player.h"

class ArtificialEnemy : public Player {
public:
    void PlayerStart();
    bool PlayerTurn(Player& enemy);
};