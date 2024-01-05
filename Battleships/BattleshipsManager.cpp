#include "BattleshipsManager.h"

using namespace std;

BattleshipsManager::BattleshipsManager(string name1, string name2, int numberOfPlayers) {
	player1.Name = name1;
	player2.Name = name2;
    mode = numberOfPlayers;

    ClearConsole();
    player1.PlayerStart();

    ClearConsole();
    if (mode == 2)
        player2.PlayerStart();
    else if (mode == 1)
        enemy.PlayerStart();
}

void BattleshipsManager::LetTheGameBegin() {
    Player *currentPlayer = &player1;

    while (true)
    {
        if (mode == 2)
            if (NextTurn(player1, player2)) return;
            if (NextTurn(player2, player1)) return;
        else if (mode == 1)
            if (NextTurn(player1, enemy)) return;
            if (NextTurn(enemy, player1)) return;
    }
}

bool BattleshipsManager::NextTurn(Player &activePlayer, Player &activeEnemy) {
    while (activePlayer.PlayerTurn(activeEnemy))
    {
        if (activeEnemy.GetVesselCount())
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
            cout << "Continue?" << endl;
            cout << "Y/y: ";
            cin >> answer;
        }
    }
    return false;
}