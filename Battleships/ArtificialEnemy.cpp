#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <ctime>
#include <cstring>
#include "Display.h"
#include "ArtificialEnemy.h"

using namespace std;

void ArtificialEnemy::PlayerStart()
{
    cout << "----------" << endl;
    cout << Name << " (AI):" << endl;
    cout << "----------" << endl;
    cout << endl;

    cout << "Would you like to upload your battleships' placement from file?" << endl;
    cout << "Y/N?: Y" << endl;

    for (int i = 0; i <= SHIPS_AMOUNT; i++)
    {
        Battleship& battleship = battleships[i];

        cout << endl << "Uploading vessel " << i + 1 << endl;

        do {
            battleship.EraseBattleshipCoordinates();

            unsigned seed = time(0);
            srand(seed);
            battleship.positionLetter = 'A' + rand() % 10;

            char letters[] = "ruld";
            battleship.directionLetter = letters[rand() % 4];

            int max = 10, min = 1;
            int range = max - min + 1;
            battleship.positionNumber = rand() % range + min;

            int lengths[] = { 2, 3, 4, 6 };
            battleship.length = lengths[rand() % 4];

            battleship.WriteBattleshipCoordinates();

        } while (battleship.IsColliding(ShipsBoard));
        
        switch (battleship.length)
        {
        case 2:
            twoTileShips++;
            break;
        case 3:
            threeTileShips++;
            break;
        case 4:
            fourTileShips++;
            break;
        case 6:
            sixTileShips++;
            break;
        }

        for (int j = 0; j <= i; j++)
        {
            battleships[j].AddShipCollision(ShipsBoard);
            battleships[j].AddToShipBoard(ShipsBoard);
        }
    }
    char answer = ' ';

    while (answer != 'y' && answer != 'Y')
    {
        cout << "Enemy vessels ready." << endl;
        cout << "Continue?" << endl;
        cout << "Y/y: ";
        cin >> answer;
    }
}

bool ArtificialEnemy::PlayerTurn(Player& enemy)
{
    ClearConsole();
    cout << endl;
    cout << "________________________________" << endl;
    cout << Name << "'s turn (AI):" << endl;
    cout << "--------------------------------" << endl;
    cout << endl;

    cout << "2 tile ships: " << twoTileShips << endl;
    cout << "3 tile ships: " << threeTileShips << endl;
    cout << "4 tile ships: " << fourTileShips << endl;
    cout << "6 tile ships: " << sixTileShips << endl;
    cout << endl;

    enemy.GetSunkVesselsCount();
    cout << endl;

    cout << endl << "Fire in the hole!" << endl;

    unsigned seed = time(0);
    srand(seed);
    char row = 'A' + rand() % 10;

    int max = 10, min = 1;
    int range = max - min + 1;
    int column = rand() % range + min;

    cout << row << column << endl;

    Point hitPoint;

    hitPoint.x = column - 1;
    hitPoint.y = TransformBoardChar(row);

    if (enemy.ShipsBoard[hitPoint.x][hitPoint.y] == SHIP)
    {
        cout << endl;
        cout << "Result : HIT" << endl;

        HitsBoard[hitPoint.x][hitPoint.y] = HIT;

        enemy.ShipsBoard[hitPoint.x][hitPoint.y] = HIT;

        int hitShipIdx = GetHitShipId(enemy.battleships, hitPoint);

        for (int i = 0; i < enemy.battleships[hitShipIdx].length; i++)
        {
            Point& shipCoordinate = enemy.battleships[hitShipIdx].shipsCoordinates[i];
            Point& hitCoordinate = enemy.battleships[hitShipIdx].hitsCoordinates[i];

            if (shipCoordinate.x == hitPoint.x && shipCoordinate.y == hitPoint.y)
            {
                hitCoordinate.x = shipCoordinate.x;
                hitCoordinate.y = shipCoordinate.y;

                shipCoordinate.x = -1;
                shipCoordinate.y = -1;
            }
        }

        if (enemy.battleships[hitShipIdx].IsShipSunk())
        {
            switch (enemy.battleships[hitShipIdx].length)
            {
            case 2:
                enemy.twoTileShips--;
                break;
            case 3:
                enemy.threeTileShips--;
                break;
            case 4:
                enemy.fourTileShips--;
                break;
            case 6:
                enemy.fourTileShips--;
                break;
            }

            enemy.battleships[hitShipIdx].AddHitCollision(HitsBoard);
            enemy.battleships[hitShipIdx].AddToHitBoard(HitsBoard);
        }
        return true;
    }
    else
    {
        HitsBoard[hitPoint.x][hitPoint.y] = MISS;

        cout << endl;
        cout << "Result : MISS" << endl;

        char answer = ' ';

        while (answer != 'y' && answer != 'Y')
        {
            cout << endl;
            cout << "Continue?" << endl;
            cout << "Y/y: ";
            cin >> answer;
        }

        return false;
    }
}
