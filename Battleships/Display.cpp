#include <iostream>
#include "Constants.h"
#include "Display.h"

using namespace std;

void DisplayPlayerBoard(int playerBoard[][BOARD_WIDTH])
{
    cout << endl;
    cout << "      A B C D E F G H I J" << endl;
    cout << "      ___________________" << endl;
    for (int i = 0; i < BOARD_HEIGHT; i++)
    {
        if (i + 1 == BOARD_HEIGHT)
        {
            cout << i + 1;
            cout << "  |";
        }
        else
        {
            cout << " ";
            cout << i + 1;
            cout << "  |";
        }

        for (int j = 0; j < BOARD_WIDTH; j++)
        {
            switch (playerBoard[i][j])
            {
                case SHIP:
                    cout << " O";
                    break;
                case COLLISION_AREA:
                    cout << " *";
                    break;
                case HIT:
                    cout << " X";
                    break;
                case MISS:
                    cout << " M";
                    break;
                default:
                    cout << " *"; 
                    break;
            }
        }
        cout << endl;
    }
}

void DisplayPlayerAndEnemyBoards(int playerBoard[][BOARD_WIDTH], int enemyBoard[][BOARD_WIDTH])
{
    cout << endl;
    cout << "      Ship board                     Hit board" << endl;
    cout << endl;
    std::cout << "      A B C D E F G H I J            A B C D E F G H I J" << endl;
    std::cout << "      ___________________            ___________________" << endl;
    for (int i = 0; i < BOARD_HEIGHT; i++)
    {
        if (i + 1 == BOARD_HEIGHT)
        {
            cout << i + 1;
            cout << "  |";
        }
        else
        {
            cout << " ";
            cout << i + 1;
            cout << "  |";
        }

        for (int j = 0; j < BOARD_WIDTH; j++)
        {
            switch (playerBoard[i][j])
            {
            case SHIP:
                cout << " O";
                break;
            case COLLISION_AREA:
                cout << " *";
                break;
            case HIT:
                cout << " X";
                break;
            case MISS:
                cout << " M";
                break;
            default:
                cout << " *"; break;
            }
        }

        if (i + 1 == BOARD_HEIGHT)
        {
            cout << "      ";
            cout << i + 1;
            cout << "  |";
        }
        else
        {
            cout << "       ";
            cout << i + 1;
            cout << "  |";
        }

        for (int j = 0; j < BOARD_WIDTH; j++)
        {
            switch (enemyBoard[i][j])
            {
            case SHIP:
                cout << " O";
                break;
            case COLLISION_AREA:
                cout << " *";
                break;
            case HIT:
                cout << " X";
                break;
            case MISS:
                cout << " M";
                break;
            default:
                cout << " *"; break;
            }
        }
        cout << endl;
    }
}

void ClearConsole()
{
    for (int i = 0; i < 50; i++)
    {
        std::cout << endl;
    }
}