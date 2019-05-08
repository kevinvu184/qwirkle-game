#include "GameEngine.h"
#include "TileCodes.h"

#include <array>
#include <bits/stdc++.h>
#include <iostream>
#include <random>
#include <sstream>

#define MAXIMUM_TILES_BAG 72
#define MAXIMUM_PLAYER_HAND 6
#define NUMBER_OF_COLOR 6
#define NUMBER_OF_SHAPE 6

#include <iostream>

GameEngine::GameEngine()
{
    this->playerCount = 0;
    
}

GameEngine::~GameEngine()
{

}

void GameEngine::getState(Player *p)
{

    std::cout << "\n"
              << p->getPlayerName() << ", it's your turn" << std::endl;
    printScore();
    std::cout << std::endl;

    
    std::cout << board;
    std::cout << "\nYour hand is " << std::endl;
    p->displayTileInHand();

    std::cout << "\n> ";
}

int GameEngine::countToken(std::string input)
{
    int count = 0;

    std::string s1 = "";

    std::istringstream token(input);

    while (token >> s1)
    {
        count++;
    }

    return count;
}

void GameEngine::addPlayer(Player *p)
{
    playerList[playerCount] = p;
    playerCount++;
}



void GameEngine::printScore()
{
    for (int i = 0; i < this->playerCount; i++)
    {
        std::cout << "Score for " << playerList[i]->getPlayerName() << ": " << playerList[i]->getPlayerScore() << std::endl;
    }
}

void GameEngine::scorePoint(Player *p)
{
    p->setPlayerScore(p->getPlayerScore() + 1);
}

void GameEngine::scoreQwirkle(Player *p)
{
    p->setPlayerScore(p->getPlayerScore() + 6);
}


bool GameEngine::validateFormat(std::string input)
{
    bool result = false;

    std::regex place("^place ([ROYGBP][1-6]) at ([A-Z]([0-9]|1[0-9]|2[0-5]))");
    std::regex replace("^replace ([ROYGBP][1-6])");
    if (std::regex_match(input, place) || std::regex_match(input, replace))
    {
        result = true;
    }
   
    return result;
}

bool GameEngine::validateTileExistInHand(std::string tileInput, Player *player)
{
    bool result = false;
    int size = tileInput.size();
    //tile is always a two-char representation
    char char_array[size + 1];
    strcpy(char_array, tileInput.c_str());

    //ASCII to convert character into an integer
    Tile *tileToBeCompare = new Tile(char_array[0], char_array[1] - 48);
    if (player->getPlayerHand()->contains(tileToBeCompare))
    {
        result = true;
    }

    return result;
}


std::string GameEngine::getTileFromUserInput(std::string input)
{

    std::string tile = "";

    std::istringstream token(input);

    //tile in any command is at the second position
    for (int i = 0; i < 1; i++)
    {
        token >> tile;
    }
    token >> tile;

    return tile;
}

std::string GameEngine::getLocationFromUserInput(std::string input)
{
    std::string location = "";

    std::istringstream token(input);

    for (int i = 0; i < 3; i++)
    {
        token >> location;
    }

    token >> location;

    return location;
}

void GameEngine::playGame(std::string p1, std::string p2)
{

    //tileBag created inside scope of playGame
    LinkedList *tileBag = new LinkedList();
    LinkedList *hand_1 = new LinkedList();
    LinkedList *hand_2 = new LinkedList();

    Player *player_1 = new Player(1, p1, hand_1);
    Player *player_2 = new Player(2, p2, hand_2);

    addPlayer(player_1);
    addPlayer(player_2);

    bool playerA = true;
    bool continueLoop_1 = true;
    bool continueLoop_2 = true;
    bool addTileVerify_1 = true;
    bool addTileVerify_2 = true; 

    // Create the tile bag
    shuffleAndCreateTileBag(tileBag);

    setUpTilesInitially(player_1, tileBag);
    setUpTilesInitially(player_2, tileBag);

    std::string inputFromUser = "";
    std::string tileInput = "";
    std::string gridLocation = "";

    int turn = 0;
    bool quit = false;

    //game starts here
    do
    {
        if (playerA == true)
        {
            this->getState(player_1);
            std::getline(std::cin, inputFromUser);
            if (std::cin.eof() == true)
            {
                std::cout << "\n\nGoodbye\n";
                quit = true;
            }
        }

        //at the start of the game we do not have to checkLegalMove() on board
        if (turn == 0 && playerA == true)
        {

            if (quit != true)
            {

                do
                {

                    //saveGame and invalid input (include invalidformat, invalidtileexistinhand and invalidmove ) goes into here
                    if (validateFormat(inputFromUser) == false || validateTileExistInHand(getTileFromUserInput(inputFromUser), player_1) == false)
                    {
                        //suppose player saves game many times
                        while (inputFromUser.substr(0, 4) == "save" && validateFormat(inputFromUser) == false && countToken(inputFromUser) == 2)
                        {
                            //call saveGame() here
                            std::cout << "\nGame successfully saved\n\n";
                            std::cout << "> ";

                            //saveGame or Quit(first time input) goes into here
                            std::getline(std::cin, inputFromUser);
                            if (std::cin.eof() == true)
                            {
                                std::cout << "\nGoodbye\n";
                                quit = true;
                            }
                        }
                        while ((validateFormat(inputFromUser) == false || validateTileExistInHand(getTileFromUserInput(inputFromUser), player_1) == false) && quit != true)
                        {
                            if (inputFromUser.substr(0, 4) != "save" || countToken(inputFromUser) != 2)
                            {
                                std::cout << "\nInvalid Input\n";
                                std::cout << "> ";
                                std::getline(std::cin, inputFromUser);
                                if (std::cin.eof() == true)
                                {
                                    std::cout << "\nGoodbye\n";
                                    quit = true;
                                }
                            }
                            else
                            {
                                if (countToken(inputFromUser) == 2)
                                {
                                    //call saveGame() here
                                    std::cout << "\nGame successfully saved\n\n";
                                    std::cout << "> ";
                                    std::getline(std::cin, inputFromUser);
                                    if (std::cin.eof() == true)
                                    {
                                        std::cout << "\nGoodbye\n";
                                        quit = true;
                                    }
                                }
                            }
                        }
                        if (addTileVerify_1 == false)
                        {
                            std::cout << "\nInvalid Input\n";
                            std::cout << "> ";

                            std::getline(std::cin, inputFromUser);
                            if (std::cin.eof() == true)
                            {
                                std::cout << "\nGoodbye\n";
                                quit = true;
                            }
                        }
                    }

                    //after save and invalid input and do not quit goes into here for further validation
                    //or input correctly the first time
                    if (quit != true)
                    {

                        if (countToken(inputFromUser) == 4)
                        {

                            tileInput = getTileFromUserInput(inputFromUser);        //get the second element
                            gridLocation = getLocationFromUserInput(inputFromUser); // get the fourth element

                            if (validateFormat(inputFromUser) == true && validateTileExistInHand(tileInput, player_1) == true)
                            {

                                //pass all the validation for placing
                                playerA = false;
                                //board processing
                                // linkedlist processing here
                                int size = tileInput.size();
                                //tile is always a two-char representation
                                char cTileInput[size + 1];
                                strcpy(cTileInput, tileInput.c_str());

                                Tile *newTile = new Tile(cTileInput[0], cTileInput[1] - 48);
                                

                                if (gridLocation.size() == 2)
                                {
                                    int sizeLocation = gridLocation.size();

                                    char cSizeInput[sizeLocation + 1];
                                    strcpy(cSizeInput, gridLocation.c_str());
                                    //cSizeInput[0] = y , cSizeInput[1] = x
                                    Coordinate c = Coordinate(cSizeInput[0], cSizeInput[1] - 48, *newTile);
                                    if (!board.addTileAt(c))
                                    {
                                        addTileVerify_1 = false;
                                    }
                                    else
                                    {
                                        player_1->setPlayerScore(board.totalPoint(c));
                                        player_1->getPlayerHand()->deleteTile(newTile);
                                        player_1->getPlayerHand()->addBack(tileBag->getFront());
                                        tileBag->deleteFront();
                                    }
                                }
                                else
                                {
                                    int sizeLocation = gridLocation.size();

                                    char cSizeInput[sizeLocation + 1];
                                    strcpy(cSizeInput, gridLocation.c_str());

                                    int x = (cSizeInput[1] - 48) * 10 + (cSizeInput[2] - 48);

                                    //cSizeInput[0] = y, x = x coordinate
                                    Coordinate c = Coordinate(cSizeInput[0], x, *newTile);
                                    if (!board.addTileAt(c))
                                    {
                                        addTileVerify_1 = false;
                                    }
                                    else
                                    {
                                        player_1->setPlayerScore(board.totalPoint(c));
                                        player_1->getPlayerHand()->deleteTile(newTile);
                                        player_1->getPlayerHand()->addBack(tileBag->getFront());
                                        tileBag->deleteFront();
                                    }
                                }          
                                
                                delete newTile;
                
                                turn++;
                                continueLoop_1 = false;
                            }
                        }
                        else if (countToken(inputFromUser) == 2)
                        {
                            tileInput = getTileFromUserInput(inputFromUser);
                            if (validateFormat(inputFromUser) && validateTileExistInHand(tileInput, player_1))
                            {
                                //pass all the validation for replacing tile

                                playerA = false;
                                //board processing
                                //linkedlist processing here
                                int size = tileInput.size();
                                //tile is always a two-char representation
                                char cTileInput[size + 1];
                                strcpy(cTileInput, tileInput.c_str());

                                Tile *newTile = new Tile(cTileInput[0], cTileInput[1] - 48);
                                player_1->getPlayerHand()->deleteTile(newTile);
                                //Place the tile on the board
                                player_1->getPlayerHand()->addBack(tileBag->getFront());
                                tileBag->deleteFront();
                                delete newTile;
                                //update game score
                                
                                turn++;
                                continueLoop_1 = false;
                            }
                        }
                    }

                } while ((validateFormat(inputFromUser) == false || validateTileExistInHand(getTileFromUserInput(inputFromUser), player_1) == false) && quit != true && continueLoop_1 == true && addTileVerify_1 == false);
                //quit != true to reprompt otherwise exit reprompt and end program
                //validateLocationExist() and validateLegalMove() only apply for placing tile
                //so we have to have a special case for replacing  inside each method implementation
            }
        }
        else if (turn != 0)
        {

            //if player 1 does not want to quit start validating input
            if (quit != true)
            {

                if (playerA == true)
                {
                    do
                    {
                        //saveGame goes into this thread
                        if (validateFormat(inputFromUser) == false || validateTileExistInHand(getTileFromUserInput(inputFromUser), player_1) == false || addTileVerify_1 == false)
                        {
                            //suppose player saves game many times
                            while (inputFromUser.substr(0, 4) == "save" && validateFormat(inputFromUser) == false && countToken(inputFromUser) == 2)
                            {
                                //call saveGame() here
                                std::cout << "\nGame successfully saved\n\n";
                                std::cout << "> ";

                                addTileVerify_1 = true;

                                std::getline(std::cin, inputFromUser);
                                if (std::cin.eof() == true)
                                {
                                    std::cout << "\nGoodbye\n";
                                    quit = true;
                                }
                            }
                            while ((validateFormat(inputFromUser) == false || validateTileExistInHand(getTileFromUserInput(inputFromUser), player_1) == false) && quit != true)
                            {
                                if (inputFromUser.substr(0, 4) != "save" || countToken(inputFromUser) != 2)
                                {
                                    std::cout << "\nInvalid Input\n";
                                    std::cout << "> " << std::flush;

                                    addTileVerify_1 = true;

                                    std::getline(std::cin, inputFromUser);
                                    if (std::cin.eof() == true)
                                    {
                                        std::cout << "\nGoodbye\n";
                                        quit = true;
                                    }
                                }
                                else
                                {
                                    if (countToken(inputFromUser) == 2)
                                    {
                                        //call saveGame() here
                                        std::cout << "\nGame successfully saved\n\n";
                                        std::cout << "> ";
                                        addTileVerify_1 = true;

                                        std::getline(std::cin, inputFromUser);
                                        if (std::cin.eof() == true)
                                        {
                                            std::cout << "\nGoodbye\n";
                                            quit = true;
                                        }
                                    }
                                }
                            }
                            if (addTileVerify_1 == false)
                            {
                                std::cout << "\nInvalid Input\n";
                                std::cout << "> ";

                                std::getline(std::cin, inputFromUser);
                                if (std::cin.eof() == true)
                                {
                                    std::cout << "\nGoodbye\n";
                                    quit = true;
                                }
                            }
                        }

                        //invalid two times
                        if (quit != true)
                        {

                            if (countToken(inputFromUser) == 4)
                            {

                                tileInput = getTileFromUserInput(inputFromUser);        //get the second element
                                gridLocation = getLocationFromUserInput(inputFromUser); // get the fourth element

                                if (validateFormat(inputFromUser) == true && validateTileExistInHand(tileInput, player_1) == true)
                                {

                                    //pass all the validation for placing

                                    //board processing here
                                    //doing linkedlist processing here
                                    int size = tileInput.size();
                                    //tile is always a two-char representation
                                    char cTileInput[size + 1];
                                    strcpy(cTileInput, tileInput.c_str());

                                    Tile *newTile = new Tile(cTileInput[0], cTileInput[1] - 48);
                                    
                                    //Place the tile on the board
                                    if (gridLocation.size() == 2)
                                    {
                                        int sizeLocation = gridLocation.size();

                                        char cSizeInput[sizeLocation + 1];
                                        strcpy(cSizeInput, gridLocation.c_str());
                                        //cSizeInput[0] = y , cSizeInput[1] = x
                                        Coordinate c = Coordinate(cSizeInput[0], cSizeInput[1] - 48, *newTile);
                                        if (!board.addTileAt(c))
                                        {
                                            addTileVerify_1 = false;
                                            playerA = true;
                                            continueLoop_1 = true;
                                        }
                                        else
                                        {
                                            player_1->setPlayerScore(board.totalPoint(c));
                                            if (board.totalPoint(c) == 12)
                                            {
                                                std::cout << "\nQWIRKLE!!!\n";
                                            }
                                            player_1->getPlayerHand()->deleteTile(newTile);
                                            player_1->getPlayerHand()->addBack(tileBag->getFront());
                                            tileBag->deleteFront();

                                            addTileVerify_1 = true;
                                            playerA = false;
                                            continueLoop_1 = false;
                                        }
                                    }
                                    else
                                    {
                                        int sizeLocation = gridLocation.size();

                                        char cSizeInput[sizeLocation + 1];
                                        strcpy(cSizeInput, gridLocation.c_str());

                                        int x = (cSizeInput[1] - 48) * 10 + (cSizeInput[2] - 48);

                                        //cSizeInput[0] = y, x = x coordinate
                                        Coordinate c = Coordinate(cSizeInput[0], x, *newTile);
                                        if (!board.addTileAt(c))
                                        {
                                            addTileVerify_1 = false;
                                            playerA = true;
                                            continueLoop_1 = true;
                                        }
                                        else
                                        {
                                            player_1->setPlayerScore(board.totalPoint(c));
                                            if (board.totalPoint(c) == 12)
                                            {
                                                std::cout << "\nQWIRKLE!!!\n";
                                            }
                                            player_1->getPlayerHand()->deleteTile(newTile);
                                            player_1->getPlayerHand()->addBack(tileBag->getFront());
                                            tileBag->deleteFront();

                                            addTileVerify_1 = true;
                                            playerA = false;
                                            continueLoop_1 = false;
                                        }
                                    }
             
                                    delete newTile;
                             
                                    turn++;
                                    
                                }
                            }
                            else if (countToken(inputFromUser) == 2)
                            {
                                tileInput = getTileFromUserInput(inputFromUser);
                                if (validateFormat(inputFromUser) && validateTileExistInHand(tileInput, player_1))
                                {
                                    //pass all the validation for replacing

                                    playerA = false;
                                   
                                    int size = tileInput.size();
                                    //tile is always a two-char representation
                                    char cTileInput[size + 1];
                                    strcpy(cTileInput, tileInput.c_str());

                                    Tile *newTile = new Tile(cTileInput[0], cTileInput[1] - 48);
                                    player_1->getPlayerHand()->deleteTile(newTile);

                                    player_1->getPlayerHand()->addBack(tileBag->getFront());
                                    tileBag->deleteFront();
                                    delete newTile;
                            
                                    addTileVerify_1 = true;
                                    turn++;
                                    continueLoop_1 = false;
                                }
                            }
                        }
                    } while ((validateFormat(inputFromUser) == false || validateTileExistInHand(getTileFromUserInput(inputFromUser), player_1) == false || addTileVerify_1 == false) && quit != true && continueLoop_1 == true);
                }

                //redundant ???? - NO as player 1 save and quit
                //we do not want the game to print out game state for player 2

                if (quit != true && playerA == false)
                {

                    this->getState(player_2);

                    std::getline(std::cin, inputFromUser);
                    if (std::cin.eof())
                    {
                        std::cout << "\nGoodbye\n";
                        quit = true;
                    }

                    //if player 2 does not want to quit
                    if (quit != true)
                    {
                        do
                        {
                            if (validateFormat(inputFromUser) == false || validateTileExistInHand(getTileFromUserInput(inputFromUser), player_2) == false || addTileVerify_2 == false)
                            {
                                //suppose player wants to save game many times
                                while (inputFromUser.substr(0, 4) == "save" && validateFormat(inputFromUser) == false && countToken(inputFromUser) == 2)
                                {
                                    //call saveGame() here
                                    std::cout << "\nGame successfully saved\n\n";
                                    std::cout << "> ";
                                    addTileVerify_2 = true;
                                    std::getline(std::cin, inputFromUser);
                                    if (std::cin.eof())
                                    {
                                        quit = true;
                                        std::cout << "\nGoodbye\n";
                                    }
                                }
                                while ((validateFormat(inputFromUser) == false || validateTileExistInHand(getTileFromUserInput(inputFromUser), player_2) == false) && quit != true)
                                {
                                    if (inputFromUser.substr(0, 4) != "save" || countToken(inputFromUser) != 2)
                                    {
                                        std::cout << "\nInvalid Input\n";
                                        std::cout << "> ";
                                        
                                        addTileVerify_2 = true;

                                        std::getline(std::cin, inputFromUser);
                                        if (std::cin.eof() == true)
                                        {
                                            std::cout << "\nGoodbye\n";
                                            quit = true;
                                        }
                                    }
                                    else
                                    {
                                        if (countToken(inputFromUser) == 2)
                                        {
                                            //call saveGame() here
                                            std::cout << "\nGame successfully saved\n\n";
                                            std::cout << "> ";
                                             
                                            addTileVerify_2 = true;

                                            std::getline(std::cin, inputFromUser);
                                            if (std::cin.eof() == true)
                                            {
                                                std::cout << "\nGoodbye\n";
                                                quit = true;
                                            }
                                        }
                                    }
                                }
                                if (addTileVerify_2 == false)
                                {
                                    std::cout << "\nInvalid Input\n";
                                    std::cout << "> ";

                                    std::getline(std::cin, inputFromUser);
                                    if (std::cin.eof() == true)
                                    {
                                        std::cout << "\nGoodbye\n";
                                        quit = true;
                                    }
                                }
                            }
                            if (quit != true)
                            {

                                if (countToken(inputFromUser) == 4)
                                {

                                    tileInput = getTileFromUserInput(inputFromUser);        //get the second element
                                    gridLocation = getLocationFromUserInput(inputFromUser); // get the fourth element

                                    if (validateFormat(inputFromUser) == true && validateTileExistInHand(tileInput, player_2))
                                    {

                                        //pass all the validation for placing
    
                                        
                                        int size = tileInput.size();
                                        //tile is always a two-char representation
                                        char cTileInput[size + 1];
                                        strcpy(cTileInput, tileInput.c_str());

                                        Tile *newTile = new Tile(cTileInput[0], cTileInput[1] - 48);
                                        
                                        //Place the tile on the board
                                        if (gridLocation.size() == 2)
                                        {
                                            int sizeLocation = gridLocation.size();

                                            char cSizeInput[sizeLocation + 1];
                                            strcpy(cSizeInput, gridLocation.c_str());
                                            //cSizeInput[0] = y , cSizeInput[1] = x
                                            Coordinate c = Coordinate(cSizeInput[0], cSizeInput[1] - 48, *newTile);
                                           
                                            if (!board.addTileAt(c))
                                            {
                                                addTileVerify_2 = false;
                                                continueLoop_2 = true;
                                                playerA = false;
                                            }
                                            else
                                            {
                                                player_2->setPlayerScore(board.totalPoint(c));
                                                if (board.totalPoint(c) == 12)
                                                {
                                                    std::cout << "\nQWIRKLE!!!\n";
                                                }
                                                player_2->getPlayerHand()->deleteTile(newTile);
                                                player_2->getPlayerHand()->addBack(tileBag->getFront());
                                                tileBag->deleteFront();
                                                
                                                continueLoop_2 = false;
                                                playerA = true;
                                                addTileVerify_2 = true;
                                            }
                                        }
                                        else
                                        {
                                            int sizeLocation = gridLocation.size();

                                            char cSizeInput[sizeLocation + 1];
                                            strcpy(cSizeInput, gridLocation.c_str());

                                            int x = (cSizeInput[1] - 48) * 10 + (cSizeInput[2] - 48);

                                            //cSizeInput[0] = y, x = x coordinate
                                            Coordinate c = Coordinate(cSizeInput[0], x, *newTile);
                                            if (!board.addTileAt(c))
                                            {
                                                addTileVerify_2 = false;
                                                playerA = false;
                                                continueLoop_2 = true;
                                            }
                                            else
                                            {
                                                player_2->setPlayerScore(board.totalPoint(c));
                                                if (board.totalPoint(c) == 12)
                                                {
                                                    std::cout << "\nQWIRKLE!!!\n";
                                                }
                                                player_2->getPlayerHand()->deleteTile(newTile);
                                                player_2->getPlayerHand()->addBack(tileBag->getFront());
                                                tileBag->deleteFront();

                                                playerA = true;
                                                continueLoop_2 = false;
                                                addTileVerify_2 = true;
                                            }
                                        }
                                        
                                        delete newTile;
                                        turn++;
                                    }
                                }
                                else
                                {

                                    tileInput = getTileFromUserInput(inputFromUser);
                                    if (validateFormat(inputFromUser) && validateTileExistInHand(tileInput, player_2))
                                    {

                                        //pass all the validation for replacing

                                        int size = tileInput.size();

                                        //tile is always a two-char representation
                                        char cTileInput[size + 1];
                                        strcpy(cTileInput, tileInput.c_str());

                                        Tile *newTile = new Tile(cTileInput[0], cTileInput[1] - 48);
                                        player_2->getPlayerHand()->deleteTile(newTile);
                                     
                                        player_2->getPlayerHand()->addBack(tileBag->getFront());
                                        tileBag->deleteFront();
                                        delete newTile;

                                        //update game state
                                        playerA = true;
                                        addTileVerify_2 = true;
                                        turn++;
                                        continueLoop_2 = false;
                                    }
                                }
                            }

                        } while ((validateFormat(inputFromUser) == false || validateTileExistInHand(getTileFromUserInput(inputFromUser), player_2) == false || addTileVerify_2 == false) && quit != true && continueLoop_2 == true);
                    }
                }
            }
        }

    } while ((tileBag->getSize() != 0 || ((player_1->getPlayerHand()->getSize() != 0) && player_2->getPlayerHand()->getSize() != 0)) && quit != true);

    //only display when the game ends not QUIT
    if (quit == false)
    {
        std::cout << "Game over\n";
        std::cout << "Score for " << player_1->getPlayerName() << ": " << player_1->getPlayerScore() << std::endl;
        std::cout << "Score for " << player_2->getPlayerName() << ": " << player_2->getPlayerScore() << std::endl;

        if (player_1->getPlayerScore() > player_2->getPlayerScore())
        {
            std::cout << "Player " << player_1->getPlayerScore() << " won!\n";
        }
        else
        {
            std::cout << "Player " << player_2->getPlayerScore() << " won!\n";
        }
        std::cout << "\nGoodbye";
    }

    delete hand_1;
    delete hand_2;
    delete tileBag;
}

void GameEngine::setUpTilesInitially(Player *player, LinkedList *tileBag)
{
    for (int i = 0; i < MAXIMUM_PLAYER_HAND; ++i)
    {
        player->getPlayerHand()->addBack(tileBag->getFront());
        tileBag->deleteFront();
    }
}

int GameEngine::randomNumberGenerate()
{
    std::random_device rd;
    std::mt19937 eng(rd());
    std::uniform_int_distribution<> distr(0, 5);

    return distr(eng);
}

void GameEngine::shuffleAndCreateTileBag(LinkedList *tileBag)
{

    std::array<char, NUMBER_OF_COLOR> colours = {RED, ORANGE, GREEN, BLUE, PURPLE, YELLOW};
    std::array<int, NUMBER_OF_SHAPE> shapes = {CIRCLE, STAR_4, DIAMOND, SQUARE, STAR_6, CLOVER};

    //the algorithm can be found in linkedlist.cpp
    for (int count = 0; count < MAXIMUM_TILES_BAG; count++)
    {
        Tile *tileToBeAdded = new Tile(colours[randomNumberGenerate()], shapes[randomNumberGenerate()]);
        while (tileBag->tileExist(tileToBeAdded) == 2)
        {
            delete tileToBeAdded;
            tileToBeAdded = new Tile(colours[randomNumberGenerate()], shapes[randomNumberGenerate()]);
        }

        tileBag->addBack(tileToBeAdded);
    }
}
