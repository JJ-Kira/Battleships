#include "BattleshipsManager.h"

using namespace std;

BattleshipsManager::BattleshipsManager(string name1, string name2) {
	player1.Name = name1;
	player2.Name = name2;

    ClearConsole();
    player1.PlayerStart();

    ClearConsole();
    player2.PlayerStart();
}

void BattleshipsManager::LetTheGameBegin() {
    Player currentPlayer = player1;

    while (true)
    {
        if (NextTurn(player1, player2)) return;
        if (NextTurn(player2, player1)) return;
    }
}

bool BattleshipsManager::NextTurn(Player activePlayer, Player activeEnemy) {
    while (activePlayer.PlayerTurn(activeEnemy))
    {
        // If opposite player runs out of ships, the game ends 
        if (activeEnemy.sixTileShips + activeEnemy.fourTileShips + activeEnemy.threeTileShips + activeEnemy.twoTileShips <= 0)
        {
            ClearConsole();

            // Displays player ship board and hit board
            Display2Boards(activePlayer.ShipBoard, activePlayer.HitBoard);

            cout << endl;
            cout << "PLAYER 1 has won" << endl;

            return true;
        }

        char answer = ' ';
        // Improvised pause
        while (answer != 'y' && answer != 'Y')
        {
            cout << endl;
            cout << "Continue game?" << endl;
            cout << "Type Y/y : ";
            cin >> answer;
        }
    }
    return false;
}