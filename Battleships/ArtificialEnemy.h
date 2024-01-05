#pragma once
#include <cstring>
#include "Constants.h"
#include "Battleship.h"
#include "Player.h"

class ArtificialEnemy : public Player {
public:
    ArtificialEnemy(const std::string& name);
    void PlayerStart() override;
    bool PlayerTurn(Player& enemy) override;
};