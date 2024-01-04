#include <iostream>
#include <cstring>
#include <string>
#include <fstream>
#include "Player.h"
#include "Display.h"
#include "BattleshipsManager.h"

int main()
{
    BattleshipsManager battleships = BattleshipsManager("JJ", "Chibi");

    battleships.LetTheGameBegin();

    return 0;
}