#pragma once
#include <cstring>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include "Player.h"
#include "Display.h"

using namespace std;

int Player::GetShipIdx(string searchedConfig)
{
    
    char posLetter = ' ', dirLetter = ' ';
    int posNumber = 0, length = 0;

    
    posLetter = searchedConfig[0];

    if (searchedConfig.length() == 6)
    {
        posNumber = searchedConfig[1] - '0';
        dirLetter = searchedConfig[3];
        length = searchedConfig[5] - '0';
    }
    else if (searchedConfig.length() == 7)
    {
        posNumber += (searchedConfig[1] - '0') * 10;
        posNumber += searchedConfig[2] - '0';
        dirLetter = searchedConfig[4];
        length = searchedConfig[6] - '0';
    }

    // Search for wanted ship in player's battleships
    for (int i = 0; i < MAX_SHIPS_AMOUNT; i++)
    {
        Battleship battleship = battleships[i];
        if (battleship.posLetter == posLetter && battleship.posNumber == posNumber &&
            battleship.dirLetter == dirLetter && battleship.length == length)
        {
            return i;
        }
    }
    return -1;
}

int Player::GetHitShipIdx(Battleship enemyBattleships[], Point hitPoint)
{

    // All elements of enemy's battleships
    for (int i = 0; i < MAX_SHIPS_AMOUNT; i++)
    {
        // All elements of enemy's battleship coordinates
        for (int j = 0; j < enemyBattleships[i].length; j++)
        {
            Point shipCoordinate = enemyBattleships[i].shipCoordinates[j];
            
            // Search for battleship's index that hitPoint belongs to
            if (enemyBattleships[i].shipCoordinates[j].x == hitPoint.x && 
                enemyBattleships[i].shipCoordinates[j].y == hitPoint.y)
            {
                return i;
            }
        }

    }

    // If smth is wrong, return -1
    return -1;
}

void Player::GetConfigFromFile()
{
    fstream userFile;
    string filePath;
   
    cout << "Please input file path : ";
    cin >> filePath;
    userFile.open(filePath, fstream::in);

    // If file can't be open
    while (!userFile.is_open())
    {
        cout << "Failed to open file" << endl;
        cout << "Please input file path : ";
        cin >> filePath;
        userFile.open(filePath, fstream::in);
    }
   
    string buffer;

    // Reading each file line until MAX_SHIPS_AMOUNT is reached
    int i;
    for (i = 0; getline(userFile, buffer) && i < MAX_SHIPS_AMOUNT; i++)
    {
        Battleship& battleship = battleships[i];
        
        // Transforming each buffer to certain data structure members
        if (buffer.length() == 6 || buffer.length() == 7)
        {
            battleship.posLetter = buffer[0];
            
            if (buffer.length() == 6)
            {
                battleship.posNumber = buffer[1] - '0';
                battleship.dirLetter = buffer[3];
                battleship.length = buffer[5] - '0';
            }
            else if (buffer.length() == 7)
            {
                battleship.posNumber = (buffer[1] - '0') * 10 + (buffer[2] - '0');
                battleship.dirLetter = buffer[4];
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
        while (!battleship.CheckConfig(ShipBoard, sixTileShips, fourTileShips, threeTileShips, twoTileShips))
        {
            cout << endl;
            battleship.CorrectConfig(ShipBoard, sixTileShips, fourTileShips, threeTileShips, twoTileShips);
        }

        // Write ship coordinates, in order to check if it collides in the next step 
        battleship.WriteBattleshipCoordinates();
        
        // Running some checks to determine if already checked configurations 
        // don't collides with each other
        while (battleship.IsColliding(ShipBoard))
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
            cout << "Your ship is colliding with previously added ships" << endl;
            cout << "Position to edit : ";
            battleship.PrintConfig();
            
            cout << endl;
            
            // First erase previos coordinates
            battleship.EraseBattleshipCoordinates();
            
            cout << "Correct your ship configuration : ";
            // Second input new configuration
            battleship.InputBattleshipConfig(sixTileShips, fourTileShips, threeTileShips, twoTileShips);
            
            // Then write new coordinates
            battleship.WriteBattleshipCoordinates();
        }

        // Add area where no other ship can be put
        battleship.AddShipCollision(ShipBoard);
        
        // Add ship's image over collision area 
        battleship.AddToShipBoard(ShipBoard);

    }
    
    userFile.close();
    
    // File configuration is too short
    if (i != MAX_SHIPS_AMOUNT)
    {
        cout << endl;
        cout << "Error, too few ships in current file" << endl;
        
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
        cout << "Would you like to upload ship configuration from file?" << endl;
        cout << "Y / N? : ";
        cin >> answer;
    }
    
    if (answer == "Y" || answer == "y")
    {
        GetConfigFromFile();
        
        // Before continuing show board
        DisplayBoard(ShipBoard);

        char answer = ' ';
        // Improvised pause
        while (answer != 'y' && answer != 'Y')
        {
            cout << endl;
            cout << "Proceed?" << endl;
            cout << "Type Y/y : ";
            cin >> answer;
        }
    }
    else
    {

        for (int i = 0; i <= MAX_SHIPS_AMOUNT;)
        {
            cout << endl;
            cout << "2 tile ships: " << twoTileShips << endl;
            cout << "3 tile ships: " << threeTileShips << endl;
            cout << "4 tile ships: " << fourTileShips << endl;
            cout << "6 tile ships: " << sixTileShips << endl;
            cout << endl;
            
            string answer = " ";

            // Initially user doesn't have any ships added
            // So no edit option is given
            if (i == 0)
            {
                cout << "1. Input next ship" << endl;
                cout << "2. Show ship board" << endl;
                cout << endl;
                cout << "Choose option : ";
            }
            // If somewhere in the middle, menu is full
            else if (i < MAX_SHIPS_AMOUNT)
            {
                cout << "1. Input next ship" << endl;
                cout << "2. Edit ship configuration" << endl;
                cout << "3. Show ship board" << endl;
                cout << endl;
                cout << "Choose option : ";
            }
            //  At the end no ships should be added
            else if (i == MAX_SHIPS_AMOUNT)
            {
                cout << "1. Edit ship configuration" << endl;
                cout << "2. Show ship board" << endl;
                cout << "3. Finish" << endl;
                cout << endl;
                cout << "Choose option : ";
            }
            
            cin >> answer;
            
            // If there is no match for answer, clear console and start all over
            if (answer != "1" && answer != "2" && answer != "3")
            {
                ClearConsole();
                continue;
            }

            // Input ship option
            if (answer == "1" && i < MAX_SHIPS_AMOUNT)
            {
                Battleship& battleship = battleships[i];
                
                cout << endl;
                cout << "Input your ship configuration in format A1 R L , where A1 is starting tile, R is direction and L is length: " << endl;
                cout << "Input ship " << i + 1 << " : ";

                // Inputting ship
                battleship.InputBattleshipConfig(sixTileShips, fourTileShips, threeTileShips, twoTileShips);

                // Run checks
                while (!battleship.CheckConfig(ShipBoard, sixTileShips, fourTileShips, threeTileShips, twoTileShips))
                {
                    cout << endl;
                    battleship.CorrectConfig(ShipBoard, sixTileShips, fourTileShips, threeTileShips, twoTileShips);
                }

                // Write coordinates
                battleship.WriteBattleshipCoordinates();

                // Check if out of collision
                while (battleship.IsColliding(ShipBoard))
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
                    battleships[j].AddShipCollision(ShipBoard);
                    battleships[j].AddToShipBoard(ShipBoard);
                }

                // Everything is fine, move to next battleship
                i++;
                
                cout << endl;
            }
            // Edit ship option
            else if ((answer == "2" && i < MAX_SHIPS_AMOUNT) || (answer == "1" && i == MAX_SHIPS_AMOUNT))
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
                while (GetShipIdx(buffer) == -1)
                {
                    cout << "No ship with such config" << endl;
                    cout << "Input ship to be edited : ";
                    getline(cin, buffer);
                }

                // Ship that user wants to edit
                Battleship& battleship = battleships[GetShipIdx(buffer)];
                
                // Erase collision are
                battleship.EraseShipCollision(ShipBoard);
                
                // Erase ship's image
                battleship.EraseFromShipBoard(ShipBoard);
                
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
                    battleships[j].AddShipCollision(ShipBoard);
                    battleships[j].AddToShipBoard(ShipBoard);
                }

                cout << endl;
                cout << "Input your ship configuration in format A1 R L , where A1 is starting tile, R is direction and L is length: " << endl;
                cout << "Input new ship configuration : ";
                
                // Input new ship configuration
                battleship.InputBattleshipConfig(sixTileShips, fourTileShips, threeTileShips, twoTileShips);

                // Run checks
                while (!battleship.CheckConfig(ShipBoard, sixTileShips, fourTileShips, threeTileShips, twoTileShips))
                {
                    cout << endl;
                    battleship.CorrectConfig(ShipBoard, sixTileShips, fourTileShips, threeTileShips, twoTileShips);
                }

                // Write new coordinates
                battleship.WriteBattleshipCoordinates();

                // Check if out of collision
                while (battleship.IsColliding(ShipBoard))
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
                battleship.AddShipCollision(ShipBoard);

                // Add ship's image over collision area 
                battleship.AddToShipBoard(ShipBoard);
            }
            // Show board option
            else if ((answer == "3" && i < MAX_SHIPS_AMOUNT) || (answer == "2" && i == MAX_SHIPS_AMOUNT) || (answer == "2" && i == 0))
            {
                DisplayBoard(ShipBoard);
            }
            // Finish option
            else if ((answer == "3" && i == MAX_SHIPS_AMOUNT))
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
    
    string answer = " ";

    // Check if answer is valid
    while (answer != "1" && answer != "2" && answer != "3")
    {
        cout << "1. Show hit board" << endl;
        cout << "2. Show ship and hit boards" << endl;
        cout << "3. Fire" << endl;
        cout << "Choose option : ";
        
        cin >> answer;
        cout << endl;

        // Show hit board option
        if (answer == "1")
        {
            DisplayBoard(HitBoard);
            answer = " ";
        }
        // Show ship and hit boards option
        else if (answer == "2")
        {
            Display2Boards(ShipBoard, HitBoard);
            answer = " ";
        }
        // Fire option
        else if (answer == "3")
        {
            cout << "Input tile coordinates to fire at : ";
            break;
        }
        
        cout << endl;
    }

    // Fire mechanic

    string buffer;
    Point hitPoint;
    
    // Input in format A1
    cin >> buffer;
    
    // Check if buffer is in format A1/A10
    while (buffer.length() < 2 || buffer.length() > 3 || buffer[0] < 'A' || buffer[0] > 'J' && 
           buffer[0] < 'a' || buffer[0] > 'j' || buffer.length() == 2 && buffer[1] < '1' || 
           buffer[1] > '9' || buffer.length() == 3 && buffer[1] > '1' || buffer[2] > '0')
    {
        
        cout << endl;
        cout << "Please, input valid coordinate in format A1/A10" << endl;
        cout << "Correct your input : ";
        cin >> buffer;
    }
    
    // Format A1
    if (buffer.length() == 2)
    {
        hitPoint.x = buffer[1] - '0' - 1;
        hitPoint.y = TransformBoardChar(buffer[0]);
    }
    // Format A10
    else if (buffer.length() == 3)
    {
        hitPoint.x = BOARD_WIDTH - 1;
        hitPoint.y = TransformBoardChar(buffer[0]);
    }

    // Check if shot is successful
    if (enemy.ShipBoard[hitPoint.x][hitPoint.y] == BOARD_SHIP)
    {
        cout << endl;
        cout << "Result : HIT" << endl;
        
        // Mark player's hit board tile with H symbol
        HitBoard[hitPoint.x][hitPoint.y] = BOARD_HIT;
        
        // Mark enemy's ship board tile with H symbol
        enemy.ShipBoard[hitPoint.x][hitPoint.y] = BOARD_HIT;

        // Get hit ship index 
        int hitShipIdx = GetHitShipIdx(enemy.battleships, hitPoint);

        // Modifying ship's coordinates
        for (int i = 0; i < enemy.battleships[hitShipIdx].length; i++)
        {
            Point& shipCoordinate = enemy.battleships[hitShipIdx].shipCoordinates[i];
            Point& hitCoordinate = enemy.battleships[hitShipIdx].hitCoordinates[i];

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

        // Check if the hit ship is destroyed
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
            enemy.battleships[hitShipIdx].AddHitCollision(HitBoard);
            //  Add destroyed ship's image
            enemy.battleships[hitShipIdx].AddToHitBoard(HitBoard);
        }

        // Same player turns
        return true;
    }
    // If shot is missed
    else
    {
        // Mark missed shot board tile with F symbol
        HitBoard[hitPoint.x][hitPoint.y] = MISS;
        
        // Other player ends
        return false;
    }

}