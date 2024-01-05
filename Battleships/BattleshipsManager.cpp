#include "BattleshipsManager.h"

using namespace std;

BattleshipsManager::BattleshipsManager(string name1, string name2, int numberOfPlayers) {
    players = new Player * [2];
    players[0] = new Player(name1);
    mode = numberOfPlayers;

    ClearConsole();
    players[0]->PlayerStart();

    ClearConsole();
    if (mode == 2)
        players[1] = new Player(name2);
    else if (mode == 1)
        players[1] = new ArtificialEnemy(name2);

    players[1]->PlayerStart();
}

void BattleshipsManager::LetTheGameBegin() {
    while (true)
    {
        if (NextTurn(*players[0], *players[1])) return;
        if (NextTurn(*players[1], *players[0])) return;
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