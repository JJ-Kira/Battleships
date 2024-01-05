#include <cstring>
#include <iostream>
#include <fstream>
#include "Player.h"
#include "Display.h"

using namespace std;

int Player::GetShipId(string shipConfig)
{
    char positionLetter = ' ', directionLetter = ' ';
    int positionNumber = 0, length = 0;

    positionLetter = shipConfig[0];

    if (shipConfig.length() == 6)
    {
        positionNumber = shipConfig[1] - '0';
        directionLetter = shipConfig[3];
        length = shipConfig[5] - '0';
    }
    else if (shipConfig.length() == 7)
    {
        positionNumber += (shipConfig[1] - '0') * 10;
        positionNumber += shipConfig[2] - '0';
        directionLetter = shipConfig[4];
        length = shipConfig[6] - '0';
    }

    for (int i = 0; i < SHIPS_AMOUNT; i++)
    {
        Battleship battleship = battleships[i];
        if (battleship.positionLetter == positionLetter && battleship.positionNumber == positionNumber &&
            battleship.directionLetter == directionLetter && battleship.length == length)
            return i;
    }
    return -1;
}

int Player::GetHitShipId(Battleship enemyBattleships[], Point hitPoint)
{
    for (int i = 0; i < SHIPS_AMOUNT; i++)
    {
        for (int j = 0; j < enemyBattleships[i].length; j++)
        {
            Point shipCoordinate = enemyBattleships[i].shipsCoordinates[j];
            
            if (enemyBattleships[i].shipsCoordinates[j].x == hitPoint.x && 
                enemyBattleships[i].shipsCoordinates[j].y == hitPoint.y)
                return i;
        }
    }
    return -1;
}

void Player::ReadConfigFile()
{
    fstream file;
    string filePath;
   
    cout << "Please input the file path: ";
    cin >> filePath;
    file.open(filePath, fstream::in);

    while (!file.is_open())
    {
        cout << "Failed to open the file!" << endl;
        cout << "Please input the correct file path: ";
        cin >> filePath;
        file.open(filePath, fstream::in);
    }
   
    string buffer;

    int i;
    for (i = 0; getline(file, buffer) && i < SHIPS_AMOUNT; i++)
    {
        Battleship& battleship = battleships[i];
        
        if (buffer.length() == 6 || buffer.length() == 7)
        {
            battleship.positionLetter = buffer[0];
            
            if (buffer.length() == 6)
            {
                battleship.positionNumber = buffer[1] - '0';
                battleship.directionLetter = buffer[3];
                battleship.length = buffer[5] - '0';
            }
            else if (buffer.length() == 7)
            {
                battleship.positionNumber = (buffer[1] - '0') * 10 + (buffer[2] - '0');
                battleship.directionLetter = buffer[4];
                battleship.length = buffer[6] - '0';
            }
        }

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

        while (!battleship.CheckConfig(ShipsBoard, sixTileShips, fourTileShips, threeTileShips, twoTileShips))
        {
            cout << endl;
            battleship.CorrectConfig(ShipsBoard, sixTileShips, fourTileShips, threeTileShips, twoTileShips);
        }

        battleship.WriteBattleshipCoordinates();
        
        while (battleship.IsColliding(ShipsBoard))
        {
            switch (battleship.length)
            {
            case 2:
                twoTileShips--;
                break;
            case 3:
                threeTileShips--;
                break;
            case 4:
                fourTileShips--;
                break;
            case 6:
                sixTileShips--;
                break;
            }
            
            cout << endl;
            cout << "A ship is colliding with some previously added ships" << endl;
            cout << "Position to edit: ";
            battleship.PrintConfig();
            
            cout << endl;
            
            battleship.EraseBattleshipCoordinates();
            
            cout << "Correct the ship's configuration: ";
            battleship.InputBattleshipConfig(sixTileShips, fourTileShips, threeTileShips, twoTileShips);
            
            battleship.WriteBattleshipCoordinates();
        }

        battleship.AddShipCollision(ShipsBoard);
        
        battleship.AddToShipBoard(ShipsBoard);

    }
    
    file.close();
    
    if (i != SHIPS_AMOUNT)
    {
        cout << endl;
        cout << "Error, wrong number of ships in the file." << endl;
        
        exit(-1);
    }
}

void Player::PlayerStart()
{
    string answer = " ";
    
    cout << "----------" << endl;
    cout << Name << " :" << endl;
    cout << "----------" << endl;
    cout << endl;
    
    while (answer != "Y" && answer != "y" && answer != "N" && answer != "n")
    {
        cout << "Would you like to upload your battleships' placement from file?" << endl;
        cout << "Y/N?: ";
        cin >> answer;
    }
    
    if (answer == "Y" || answer == "y")
    {
        ReadConfigFile();

        DisplayPlayerBoard(ShipsBoard);

        char answer = ' ';
        while (answer != 'y' && answer != 'Y')
        {
            cout << endl;
            cout << "Proceed?" << endl;
            cout << "Y/y: ";
            cin >> answer;
        }
    }
    else
    {
        for (int i = 0; i <= SHIPS_AMOUNT;)
        {
            cout << endl;
            cout << "Number of 2 tile ships: " << twoTileShips << endl;
            cout << "Number of 3 tile ships: " << threeTileShips << endl;
            cout << "Number of 4 tile ships: " << fourTileShips << endl;
            cout << "Number of 6 tile ships: " << sixTileShips << endl;
            cout << endl;
            
            string answer = " ";

            if (i == 0)
            {
                cout << "1. Input next ship" << endl;
                cout << "2. Show ship board" << endl;
                cout << endl;
                cout << "Chosen option: ";
            }
            else if (i < SHIPS_AMOUNT)
            {
                cout << "1. Input the next ship" << endl;
                cout << "2. Edit ships' placement" << endl;
                cout << "3. Show the board" << endl;
                cout << endl;
                cout << "Chosen option: ";
            }
            else if (i == SHIPS_AMOUNT)
            {
                cout << "1. Edit ship configuration" << endl;
                cout << "2. Show ship board" << endl;
                cout << "3. Finish" << endl;
                cout << endl;
                cout << "Chosen option: ";
            }
            cin >> answer;
            
            if (answer != "1" && answer != "2" && answer != "3")
            {
                ClearConsole();
                continue;
            }

            if (answer == "1" && i < SHIPS_AMOUNT)
            {
                Battleship& battleship = battleships[i];
                
                cout << endl;
                cout << "Input your ship configuration in format A1 R L , where A1 is starting tile, R is direction and L is length: " << endl;
                cout << "Input ship " << i + 1 << ": ";

                battleship.InputBattleshipConfig(sixTileShips, fourTileShips, threeTileShips, twoTileShips);

                while (!battleship.CheckConfig(ShipsBoard, sixTileShips, fourTileShips, threeTileShips, twoTileShips))
                {
                    cout << endl;
                    battleship.CorrectConfig(ShipsBoard, sixTileShips, fourTileShips, threeTileShips, twoTileShips);
                }

                battleship.WriteBattleshipCoordinates();

                while (battleship.IsColliding(ShipsBoard))
                {
                    cout << "Your ship is colliding with previously added ships" << endl;
                    cout << endl;
                    cout << "Position to edit : ";
                    battleship.PrintConfig();
                    
                    switch (battleship.length)
                    {
                    case 2:
                        twoTileShips--;
                        break;
                    case 3:
                        threeTileShips--;
                        break;
                    case 4:
                        fourTileShips--;
                        break;
                    case 6:
                        sixTileShips--;
                        break;
                    }
                    
                    cout << endl;
                    
                    battleship.EraseBattleshipCoordinates();
                    
                    cout << "Correct your ship configuration : ";
                    battleship.InputBattleshipConfig(sixTileShips, fourTileShips, threeTileShips, twoTileShips);
                    
                    battleship.WriteBattleshipCoordinates();
                }

                for (int j = 0; j <= i; j++)
                {
                    battleships[j].AddShipCollision(ShipsBoard);
                    battleships[j].AddToShipBoard(ShipsBoard);
                }

                i++;
                
                cout << endl;
            }
            else if ((answer == "2" && i < SHIPS_AMOUNT) || (answer == "1" && i == SHIPS_AMOUNT))
            {
                string buffer = " ";
                
                cout << endl;
                cout << "Input your ship configuration in format A1 R L , where A1 is starting tile, R is direction and L is length: " << endl;
                cout << "Input existing ship to be edited : ";

                cin.ignore();
                getline(cin, buffer);
                cout << endl;
                
                while (GetShipId(buffer) == -1)
                {
                    cout << "No ship with such config" << endl;
                    cout << "Input ship to be edited : ";
                    getline(cin, buffer);
                }

                Battleship& battleship = battleships[GetShipId(buffer)];
                
                battleship.EraseShipCollision(ShipsBoard);
                
                battleship.EraseFromShipBoard(ShipsBoard);
                
                battleship.EraseBattleshipCoordinates();

                switch (battleship.length)
                {
                    case 2:
                        twoTileShips--;
                        break;
                    case 3:
                        threeTileShips--;
                        break;
                    case 4:
                        fourTileShips--;
                        break;
                    case 6:
                        sixTileShips--;
                        break;
                }

                for (int j = 0; j < i; j++)
                {
                    battleships[j].AddShipCollision(ShipsBoard);
                    battleships[j].AddToShipBoard(ShipsBoard);
                }

                cout << endl;
                cout << "Input your ship configuration in format A1 R L , where A1 is starting tile, R is direction and L is length: " << endl;
                cout << "Input new ship configuration : ";
                
                battleship.InputBattleshipConfig(sixTileShips, fourTileShips, threeTileShips, twoTileShips);

                while (!battleship.CheckConfig(ShipsBoard, sixTileShips, fourTileShips, threeTileShips, twoTileShips))
                {
                    cout << endl;
                    battleship.CorrectConfig(ShipsBoard, sixTileShips, fourTileShips, threeTileShips, twoTileShips);
                }

                battleship.WriteBattleshipCoordinates();

                while (battleship.IsColliding(ShipsBoard))
                {
                    cout << endl;
                    cout << "Your ship is colliding with previously added ships" << endl;
                    cout << "Position to edit : ";
                    
                    battleship.PrintConfig();
                    
                    switch (battleship.length)
                    {
                    case 2:
                        twoTileShips--;
                        break;
                    case 3:
                        threeTileShips--;
                        break;
                    case 4:
                        fourTileShips--;
                        break;
                    case 6:
                        sixTileShips--;
                        break;
                    }
                    
                    cout << endl;
                    
                    battleship.EraseBattleshipCoordinates();
                    cout << "Correct your ship configuration : ";
                    
                    battleship.InputBattleshipConfig(sixTileShips, fourTileShips, threeTileShips, twoTileShips);
                    
                    battleship.WriteBattleshipCoordinates();
                }

                battleship.AddShipCollision(ShipsBoard);
 
                battleship.AddToShipBoard(ShipsBoard);
            }

            else if ((answer == "3" && i < SHIPS_AMOUNT) || (answer == "2" && i == SHIPS_AMOUNT) || (answer == "2" && i == 0))
                DisplayPlayerBoard(ShipsBoard);
            else if ((answer == "3" && i == SHIPS_AMOUNT))
                break;
        }
    }
}

bool Player::PlayerTurn(Player& enemy)
{
    ClearConsole();
    cout << endl;
    cout << "________________________________" << endl;
    cout << Name << "'s turn:" << endl;
    cout << "--------------------------------" << endl;
    cout << endl;

    cout << "2 tile ships: " << twoTileShips << endl;
    cout << "3 tile ships: " << threeTileShips << endl;
    cout << "4 tile ships: " << fourTileShips << endl;
    cout << "6 tile ships: " << sixTileShips << endl;
    cout << endl;

    enemy.GetSunkVesselsCount();
    cout << endl;
    
    string answer = " ";

    while (answer != "1" && answer != "2" && answer != "3")
    {
        cout << "1. Show hit board" << endl;
        cout << "2. Show ship and hit boards" << endl;
        cout << "3. Fire" << endl;
        cout << "Choose option : ";
        
        cin >> answer;
        cout << endl;

        if (answer == "1")
        {
            DisplayPlayerBoard(HitsBoard);
            answer = " ";
        }
        else if (answer == "2")
        {
            DisplayPlayerAndEnemyBoards(ShipsBoard, HitsBoard);
            answer = " ";
        }
        else if (answer == "3")
        {
            cout << "Input coordinates to fire at: ";
            break;
        }
        
        cout << endl;
    }

    string buffer;
    Point hitPoint;
    
    cin >> buffer;

    while (buffer.length() < 2 || buffer.length() > 3 || buffer[0] < 'A' || buffer[0] > 'J' && 
           buffer[0] < 'a' || buffer[0] > 'j' || buffer.length() == 2 && buffer[1] < '1' || 
           buffer[1] > '9' || buffer.length() == 3 && buffer[1] > '1' || buffer[2] > '0')
    {
        
        cout << endl;
        cout << "Incorrect input." << endl;
        cout << "Correct your input: ";
        cin >> buffer;
    }
    
    if (buffer.length() == 2)
    {
        hitPoint.x = buffer[1] - '0' - 1;
        hitPoint.y = TransformBoardChar(buffer[0]);
    }
    else if (buffer.length() == 3)
    {
        hitPoint.x = BOARD_WIDTH - 1;
        hitPoint.y = TransformBoardChar(buffer[0]);
    }

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

bool Player::GetVesselCount()
{
    return sixTileShips + fourTileShips + threeTileShips + twoTileShips <= 0;
}

void Player::GetSunkVesselsCount()
{
    cout << "Sunk enemy vessels: " << 10 - (sixTileShips + fourTileShips + threeTileShips + twoTileShips) << endl;
}
