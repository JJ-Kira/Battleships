#pragma once
#include <cstring>
#include <stdlib.h>
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

    // Search for wanted ship in player's battleships
    for (int i = 0; i < SHIPS_AMOUNT; i++)
    {
        Battleship battleship = battleships[i];
        if (battleship.positionLetter == positionLetter && battleship.positionNumber == positionNumber &&
            battleship.directionLetter == directionLetter && battleship.length == length)
        {
            return i;
        }
    }
    return -1;
}

int Player::GetHitShipId(Battleship enemyBattleships[], Point hitPoint)
{

    // All elements of enemy's battleships
    for (int i = 0; i < SHIPS_AMOUNT; i++)
    {
        // All elements of enemy's battleship coordinates
        for (int j = 0; j < enemyBattleships[i].length; j++)
        {
            Point shipCoordinate = enemyBattleships[i].shipsCoordinates[j];
            
            // Search for battleship's index that hitPoint belongs to
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

    // If file can't be open
    while (!file.is_open())
    {
        cout << "Failed to open the file!" << endl;
        cout << "Please input the correct file path: ";
        cin >> filePath;
        file.open(filePath, fstream::in);
    }
   
    string buffer;

    // Reading each file line until SHIPS_AMOUNT is reached
    int i;
    for (i = 0; getline(file, buffer) && i < SHIPS_AMOUNT; i++)
    {
        Battleship& battleship = battleships[i];
        
        // Transforming each buffer to certain data structure members
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

        // Adding to specific ship amount
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

        // Run checks to determine if format A1 R L is kept
        while (!battleship.CheckConfig(ShipsBoard, sixTileShips, fourTileShips, threeTileShips, twoTileShips))
        {
            cout << endl;
            battleship.CorrectConfig(ShipsBoard, sixTileShips, fourTileShips, threeTileShips, twoTileShips);
        }

        // Write ship coordinates, in order to check if it collides in the next step 
        battleship.WriteBattleshipCoordinates();
        
        // Running some checks to determine if already checked configurations 
        // don't collides with each other
        while (battleship.IsColliding(ShipsBoard))
        {
            // If IsCollidng() is true, remove one from specific ship amount
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
            
            // First erase previos coordinates
            battleship.EraseBattleshipCoordinates();
            
            cout << "Correct the ship's configuration: ";
            // Second input new configuration
            battleship.InputBattleshipConfig(sixTileShips, fourTileShips, threeTileShips, twoTileShips);
            
            // Then write new coordinates
            battleship.WriteBattleshipCoordinates();
        }

        // Add area where no other ship can be put
        battleship.AddShipCollision(ShipsBoard);
        
        // Add ship's image over collision area 
        battleship.AddToShipBoard(ShipsBoard);

    }
    
    file.close();
    
    // File configuration is too short
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
        
        // Before continuing show board
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

            // Initially user doesn't have any ships added
            // So no edit option is given
            if (i == 0)
            {
                cout << "1. Input next ship" << endl;
                cout << "2. Show ship board" << endl;
                cout << endl;
                cout << "Chosen option: ";
            }
            // If somewhere in the middle, menu is full
            else if (i < SHIPS_AMOUNT)
            {
                cout << "1. Input the next ship" << endl;
                cout << "2. Edit ships' placement" << endl;
                cout << "3. Show the board" << endl;
                cout << endl;
                cout << "Chosen option: ";
            }
            //  At the end no ships should be added
            else if (i == SHIPS_AMOUNT)
            {
                cout << "1. Edit ship configuration" << endl;
                cout << "2. Show ship board" << endl;
                cout << "3. Finish" << endl;
                cout << endl;
                cout << "Chosen option: ";
            }
            cin >> answer;
            
            // If there is no match for answer, clear console and start all over
            if (answer != "1" && answer != "2" && answer != "3")
            {
                ClearConsole();
                continue;
            }

            // Input ship option
            if (answer == "1" && i < SHIPS_AMOUNT)
            {
                Battleship& battleship = battleships[i];
                
                cout << endl;
                cout << "Input your ship configuration in format A1 R L , where A1 is starting tile, R is direction and L is length: " << endl;
                cout << "Input ship " << i + 1 << ": ";

                // Inputting ship
                battleship.InputBattleshipConfig(sixTileShips, fourTileShips, threeTileShips, twoTileShips);

                // Run checks
                while (!battleship.CheckConfig(ShipsBoard, sixTileShips, fourTileShips, threeTileShips, twoTileShips))
                {
                    cout << endl;
                    battleship.CorrectConfig(ShipsBoard, sixTileShips, fourTileShips, threeTileShips, twoTileShips);
                }

                // Write coordinates
                battleship.WriteBattleshipCoordinates();

                // Check if out of collision
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
                    
                    // Erase previous coordinates
                    battleship.EraseBattleshipCoordinates();
                    
                    cout << "Correct your ship configuration : ";
                    // Input new configuration
                    battleship.InputBattleshipConfig(sixTileShips, fourTileShips, threeTileShips, twoTileShips);
                    
                    // Write new coordinates
                    battleship.WriteBattleshipCoordinates();
                }

                // Just in case, put all collision areas and ship's images again on the board
                for (int j = 0; j <= i; j++)
                {
                    battleships[j].AddShipCollision(ShipsBoard);
                    battleships[j].AddToShipBoard(ShipsBoard);
                }

                // Everything is fine, move to next battleship
                i++;
                
                cout << endl;
            }
            // Edit ship option
            else if ((answer == "2" && i < SHIPS_AMOUNT) || (answer == "1" && i == SHIPS_AMOUNT))
            {
                string buffer = " ";
                
                cout << endl;
                cout << "Input your ship configuration in format A1 R L , where A1 is starting tile, R is direction and L is length: " << endl;
                cout << "Input existing ship to be edited : ";

                // Get line
                cin.ignore();
                getline(cin, buffer);
                cout << endl;
                
                // Search for ship with given configuration
                while (GetShipId(buffer) == -1)
                {
                    cout << "No ship with such config" << endl;
                    cout << "Input ship to be edited : ";
                    getline(cin, buffer);
                }

                // Ship that user wants to edit
                Battleship& battleship = battleships[GetShipId(buffer)];
                
                // Erase collision are
                battleship.EraseShipCollision(ShipsBoard);
                
                // Erase ship's image
                battleship.EraseFromShipBoard(ShipsBoard);
                
                // Erase ship's coordinates
                battleship.EraseBattleshipCoordinates();

                // Removing one from specific ship amount
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

                // Just in case, put all collision areas and ship's images again on the board
                for (int j = 0; j < i; j++)
                {
                    battleships[j].AddShipCollision(ShipsBoard);
                    battleships[j].AddToShipBoard(ShipsBoard);
                }

                cout << endl;
                cout << "Input your ship configuration in format A1 R L , where A1 is starting tile, R is direction and L is length: " << endl;
                cout << "Input new ship configuration : ";
                
                // Input new ship configuration
                battleship.InputBattleshipConfig(sixTileShips, fourTileShips, threeTileShips, twoTileShips);

                // Run checks
                while (!battleship.CheckConfig(ShipsBoard, sixTileShips, fourTileShips, threeTileShips, twoTileShips))
                {
                    cout << endl;
                    battleship.CorrectConfig(ShipsBoard, sixTileShips, fourTileShips, threeTileShips, twoTileShips);
                }

                // Write new coordinates
                battleship.WriteBattleshipCoordinates();

                // Check if out of collision
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
                    
                    // Erase previous coordinates
                    battleship.EraseBattleshipCoordinates();
                    cout << "Correct your ship configuration : ";
                    
                    // Input new ship configuration
                    battleship.InputBattleshipConfig(sixTileShips, fourTileShips, threeTileShips, twoTileShips);
                    
                    // Write new coordinates
                    battleship.WriteBattleshipCoordinates();

                    
                }

                // Add area where no other ship can be put
                battleship.AddShipCollision(ShipsBoard);

                // Add ship's image over collision area 
                battleship.AddToShipBoard(ShipsBoard);
            }
            // Show board option
            else if ((answer == "3" && i < SHIPS_AMOUNT) || (answer == "2" && i == SHIPS_AMOUNT) || (answer == "2" && i == 0))
            {
                DisplayPlayerBoard(ShipsBoard);
            }
            // Finish option
            else if ((answer == "3" && i == SHIPS_AMOUNT))
            {
                break;
            }
        }
    }
}

bool Player::PlayerTurn(Player& enemy)
{
    ClearConsole();
    cout << endl;
    cout << "________________________________" << endl;
    cout << Name << "'s turn :" << endl;
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
        
        // Mark player's hit board tile with X symbol
        HitsBoard[hitPoint.x][hitPoint.y] = HIT;
        
        // Mark enemy's ship board tile with X symbol
        enemy.ShipsBoard[hitPoint.x][hitPoint.y] = HIT;

        // Get hit ship's id 
        int hitShipIdx = GetHitShipId(enemy.battleships, hitPoint);

        // Modify hit ship's coordinates
        for (int i = 0; i < enemy.battleships[hitShipIdx].length; i++)
        {
            Point& shipCoordinate = enemy.battleships[hitShipIdx].shipsCoordinates[i];
            Point& hitCoordinate = enemy.battleships[hitShipIdx].hitsCoordinates[i];

            // If ship coordinates are equal to hit point remove these coordinates
            // from ship coordinates, then add them to hit coordinates
            if (shipCoordinate.x == hitPoint.x && shipCoordinate.y == hitPoint.y)
            {
                hitCoordinate.x = shipCoordinate.x;
                hitCoordinate.y = shipCoordinate.y;
                
                shipCoordinate.x = -1;
                shipCoordinate.y = -1;
            }
        }

        // Check if the hit ship was completely destroyed
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
            
            // Add collision area around destroyed ship
            enemy.battleships[hitShipIdx].AddHitCollision(HitsBoard);
            enemy.battleships[hitShipIdx].AddToHitBoard(HitsBoard);
        }
        return true;
    }
    // If MISS
    else
    {
        // Mark missed shot board tile with M symbol
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
    cout << "Sunk vessels: " << 10 - (sixTileShips + fourTileShips + threeTileShips + twoTileShips) << endl;
}
