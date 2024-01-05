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
        // If enemy player runs out of ships, the game ends 
        if (activeEnemy.GetShipCount())
        {
            ClearConsole();

            DisplayPlayerAndEnemyBoards(activePlayer.ShipsBoard, activePlayer.HitsBoard);

            cout << endl;
            cout << activePlayer.Name << " has won!" << endl;

            return true;
        }

        char answer = ' ';

        while (answer != 'y' && answer != 'Y')
        {
            cout << endl;
            cout << "Continue game?" << endl;
            cout << "Y/y: ";
            cin >> answer;
        }
    }
    return false;
}