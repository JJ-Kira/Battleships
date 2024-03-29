#include "Battleship.h"
#include <iostream>

using namespace std;


int TransformBoardChar(char character)
{
    int widthIndex = 0;
    if (character >= 'A' && character <= 'J')
    {
        widthIndex = character - 'A';
    }
    else if (character >= 'a' && character <= 'j')
    {
        widthIndex = character - 'a';
    }

    return widthIndex;
}

void Battleship::PrintConfig()
{
    cout << positionLetter << positionNumber << " ";
    cout << directionLetter << " " << length;
}

bool Battleship::CheckConfig(int playerShipBoard[][BOARD_WIDTH], int sixTileShips, int fourTileShips, int threeTileShips, int twoTileShips)
{
    if ((positionLetter < 'A' || positionLetter > 'J') && (positionLetter < 'a' || positionLetter > 'j'))
    {
        cout << positionLetter << "!";
        return false;
    }

    if (positionNumber > 10)
    {
        cout << positionNumber << "!";
        return false;
    }

    if (directionLetter != 'r' && directionLetter != 'l' && directionLetter != 'u' && directionLetter != 'd' &&
        directionLetter != 'R' && directionLetter != 'L' && directionLetter != 'U' && directionLetter != 'D')
    {
        cout << directionLetter << "!";
        return false;
    }

    if (length < 2 || length > 6 || length == 5)
    {
        cout << length << "!";
        return false;
    }

    if (sixTileShips > SIX_TILE_SHIPS_AMOUNT)
    {
        return false;
    }

    if (fourTileShips > FOUR_TILE_SHIPS_AMOUNT)
    {
        return false;
    }

    if (threeTileShips > THREE_TILE_SHIPS_AMOUNT)
    {
        return false;
    }

    if (twoTileShips > TWO_TILE_SHIPS_AMOUNT)
    {
        return false;
    }

    int widthIndex = TransformBoardChar(positionLetter);

    if (((directionLetter == 'r' || directionLetter == 'R') && (widthIndex + length > BOARD_WIDTH)) ||
        ((directionLetter == 'l' || directionLetter == 'L') && (widthIndex - length + 1 < 0)) ||
        ((directionLetter == 'u' || directionLetter == 'U') && (positionNumber - length < 0)) ||
        ((directionLetter == 'd' || directionLetter == 'D') && (positionNumber + length - 1 > BOARD_HEIGHT)))
    {
        return false;
    }

    return true;
}

void Battleship::InputBattleshipConfig(int& sixTileShips, int& fourTileShips, int& threeTileShips, int& twoTileShips)
{
    string buffer = " ";
    cin >> buffer;
   
    positionLetter = buffer[0];
    
    if (buffer.length() == 2)
    {
        positionNumber = buffer[1] - '0';
    }
    else if (buffer.length() == 3)
    {
        positionNumber = 0;
        positionNumber += (buffer[1] - '0') * 10;
        positionNumber += buffer[2] - '0';
    }
    
    cin >> directionLetter;
    cin >> length;

    switch (length)
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
}

void Battleship::WriteBattleshipCoordinates()
{
    if (directionLetter == 'r' || directionLetter == 'R')
    {
        shipsCoordinates[0].x = positionNumber - 1;
        shipsCoordinates[0].y = TransformBoardChar(positionLetter);

        for (int i = 1; i < length; i++)
        {
            shipsCoordinates[i].x = shipsCoordinates[0].x;
            shipsCoordinates[i].y = shipsCoordinates[0].y + i;
        }
    }

    if (directionLetter == 'l' || directionLetter == 'L')
    {
        shipsCoordinates[length - 1].x = positionNumber - 1;
        shipsCoordinates[length - 1].y = TransformBoardChar(positionLetter);

        for (int i = length - 2; i >= 0; i--)
        {
            shipsCoordinates[i].x = shipsCoordinates[i + 1].x;
            shipsCoordinates[i].y = shipsCoordinates[i + 1].y - 1;
        }
    }

    if (directionLetter == 'u' || directionLetter == 'U')
    {
        shipsCoordinates[length - 1].x = positionNumber - 1;
        shipsCoordinates[length - 1].y = TransformBoardChar(positionLetter);

        for (int i = length - 2; i >= 0; i--)
        {
            shipsCoordinates[i].x = shipsCoordinates[i + 1].x - 1;
            shipsCoordinates[i].y = shipsCoordinates[i + 1].y;
        }
    }

    if (directionLetter == 'd' || directionLetter == 'D')
    {
        shipsCoordinates[0].x = positionNumber - 1;
        shipsCoordinates[0].y = TransformBoardChar(positionLetter);

        for (int i = 1; i < length; i++)
        {
            shipsCoordinates[i].x = shipsCoordinates[0].x + i;
            shipsCoordinates[i].y = shipsCoordinates[0].y;
        }
    }
}

void Battleship::EraseBattleshipCoordinates()
{
    for (int i = 0; i < MAX_SHIP_SIZE; i++)
    {
        shipsCoordinates[i].x = -2;
        shipsCoordinates[i].y = -2;
    }
}

void Battleship::CorrectConfig(int playerShipBoard[][BOARD_WIDTH], int& sixTileShips, int& fourTileShips, int& threeTileShips, int& twoTileShips)
{
    bool trigger = false;

    if ((positionLetter < 'A' || positionLetter > 'J') && (positionLetter < 'a' || positionLetter > 'j'))
    {
        cout << "Please input valid position character from A to J" << endl;
        
        trigger = true;
    }
    if (positionNumber > 10)
    {
        cout << "Please input valid position number from 1 to 10" << endl;
        
        trigger = true;
    }
    if (directionLetter != 'r' && directionLetter != 'l' && directionLetter != 'u' && directionLetter != 'd' &&
        directionLetter != 'R' && directionLetter != 'L' && directionLetter != 'U' && directionLetter != 'D')
    {
        cout << "Please input valid direction" << endl;
        
        trigger = true;
    }
    if (length < 2 || length > 6 || length == 5)
    {
        cout << "Please input valid length : 2 , 3 , 4 , 6" << endl;
        
        trigger = true;
    }

    if (sixTileShips > SIX_TILE_SHIPS_AMOUNT)
    {
        cout << "Please input valid length, you reached max number of 6 tile ships" << endl;
        
        sixTileShips--;
        
        trigger = true;
    }

    if (fourTileShips > FOUR_TILE_SHIPS_AMOUNT)
    {
        cout << "Please input valid length, you reached max number of 4 tile ships" << endl;
        
        fourTileShips--;
        
        trigger = true;
    }

    if (threeTileShips > THREE_TILE_SHIPS_AMOUNT)
    {
        cout << "Please input valid length, you reached max number of 3 tile ships" << endl;
        
        threeTileShips--;
        
        trigger = true;
    }

    if (twoTileShips > TWO_TILE_SHIPS_AMOUNT)
    {
        cout << "Please input valid length, you reached max number of 2 tile ships" << endl;
        
        twoTileShips--;
        
        trigger = true;
    }

    int widthIndex = TransformBoardChar(positionLetter);

    if (((directionLetter == 'r' || directionLetter == 'R') && (widthIndex + length > BOARD_WIDTH)) ||
        ((directionLetter == 'l' || directionLetter == 'L') && (widthIndex - length + 1 < 0)) ||
        ((directionLetter == 'u' || directionLetter == 'U') && (positionNumber - length < 0)) ||
        ((directionLetter == 'd' || directionLetter == 'D') && (positionNumber + length - 1 > BOARD_HEIGHT)))
    {
        cout << "Your ship is too long to fit the board" << endl;
        
        trigger = true;
    }

    if (trigger)
    {
        cout << endl;
        cout << "Position to edit : ";
        PrintConfig();
        cout << endl;
        
        InputBattleshipConfig(sixTileShips, fourTileShips, threeTileShips, twoTileShips);
    }
}

bool Battleship::IsColliding(int playerShipBoard[][BOARD_WIDTH])
{
    for (int i = 0; i < length; i++)
    {
        int x = shipsCoordinates[i].x;
        int y = shipsCoordinates[i].y;
        
        if (playerShipBoard[x][y] == COLLISION_AREA || playerShipBoard[x][y] == SHIP)
        {
            return true;
        }
    }
    return false;
}

bool Battleship::IsShipSunk()
{
    for (int i = 0; i < length; i++)
    {
        if (shipsCoordinates[i].x != -1 && shipsCoordinates[i].y != -1)
        {
            return false;
        }
    }
    return true;
}

void Battleship::AddHitCollision(int playerHitBoard[][BOARD_WIDTH])
{
    int x1 = hitsCoordinates[0].x - 1;
    int y1 = hitsCoordinates[0].y - 1;
    int x2 = hitsCoordinates[length - 1].x + 1;
    int y2 = hitsCoordinates[length - 1].y + 1;

    for (int i = x1; i <= x2; i++)
    {
        for (int j = y1; j <= y2; j++)
        {
            if (i >= 0 && j >= 0 && i < BOARD_HEIGHT && j < BOARD_HEIGHT)
            {
                playerHitBoard[i][j] = COLLISION_AREA;
            }
        }
    }

}

void Battleship::AddShipCollision(int playerShipBoard[][BOARD_WIDTH])
{
    int x1 = shipsCoordinates[0].x - 1;
    int y1 = shipsCoordinates[0].y - 1;
    int x2 = shipsCoordinates[length - 1].x + 1;
    int y2 = shipsCoordinates[length - 1].y + 1;

    for (int i = x1; i <= x2; i++)
    {
        for (int j = y1; j <= y2; j++)
        {
            if (i >= 0 && j >= 0 && i < BOARD_HEIGHT && j < BOARD_HEIGHT)
            {
                playerShipBoard[i][j] = COLLISION_AREA;
            }
        }
    }

}

void Battleship::EraseShipCollision(int playerShipBoard[][BOARD_WIDTH])
{
    int x1 = shipsCoordinates[0].x - 1;
    int y1 = shipsCoordinates[0].y - 1;
    int x2 = shipsCoordinates[length - 1].x + 1;
    int y2 = shipsCoordinates[length - 1].y + 1;

    for (int i = x1; i <= x2; i++)
    {
        for (int j = y1; j <= y2; j++)
        {
            if (i >= 0 && j >= 0 && i < BOARD_HEIGHT && j < BOARD_HEIGHT)
            {
                playerShipBoard[i][j] = WATER;
            }
        }
    }

}

void Battleship::AddToHitBoard(int playerHitBoard[][BOARD_WIDTH])
{
    for (int i = 0; i < length; i++)
    {
        int x = hitsCoordinates[i].x;
        int y = hitsCoordinates[i].y;
        playerHitBoard[x][y] = SHIP;
    }
}

void Battleship::AddToShipBoard(int playerShipBoard[][BOARD_WIDTH])
{
    for (int i = 0; i < length; i++)
    {
        int x = shipsCoordinates[i].x;
        int y = shipsCoordinates[i].y;
        playerShipBoard[x][y] = SHIP;
    }
}

void Battleship::EraseFromShipBoard(int playerShipBoard[][BOARD_WIDTH])
{
    for (int i = 0; i < length; i++)
    {
        int x = shipsCoordinates[i].x;
        int y = shipsCoordinates[i].y;
        playerShipBoard[x][y] = WATER;
    }
}
