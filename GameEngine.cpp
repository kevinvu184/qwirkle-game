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
#define COMMAND_SIZE_WHEN_PLACE_TILE 4
#define COMMAND_SIZE_WHEN_REPLACE_TILE 2

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

void GameEngine::saveGame(std::string filename, Player* player, LinkedList* tileBag){
  std::ofstream outFile;
  outFile.open(filename);
  for (int i = 0; i < this->playerCount; i++){
    outFile<< playerList[i]->getPlayerName() << std::endl;
    outFile<< playerList[i]->getPlayerScore() << std::endl;
    outFile<< playerList[i]->getPlayerHand()->displayList() << std::endl;
  }
  
  outFile<<"\n\n\n\n\n\n\n\n\n         PRINT BOARD HERE               \n\n\n\n\n\n\n\n\n";

  //print Tile bag
  outFile << tileBag->displayList() << std::endl;
  //Display Turn
  outFile << player->getPlayerName()<< std::endl;

  outFile.close();

}

std::string GameEngine::getNameOfFileFromUserInput(std::string input)
{
    std::string fileName = "";

    std::istringstream token(input);

    //tile in any command is at the second position
    for(int i = 0; i < 1; i++)
    {
        token>>fileName;
    }
    token>>fileName;


    return fileName;
}

void GameEngine::printMessageWhenSaveGame(std::string& inputFromUser, Player* player, LinkedList* tileBag, bool& quitGame)
{
      while (inputFromUser.substr(0, 4) == "save" && validateFormat(inputFromUser) == false && countToken(inputFromUser) == 2)
      {
                //call saveGame() here
                saveGame(getNameOfFileFromUserInput(inputFromUser), player, tileBag);
                std::cout << "\nGame successfully saved\n\n";
                std::cout << "> ";

                //saveGame or quitGame(first time input) goes into here
                std::getline(std::cin, inputFromUser);
                if (std::cin.eof() == true)
                {
                    std::cout << "\nGoodbye\n";
                    quitGame = true;
                }
      }
}

void GameEngine::printMessageWhenInvalidFormat(std::string& inputFromUser, Player* player, LinkedList* tileBag, bool& quitGame, bool& ableToAdd)
{
    while ((validateFormat(inputFromUser) == false || validateTileExistInHand(getTileFromUserInput(inputFromUser), player) == false) && quitGame != true)
    {
                if (inputFromUser.substr(0, 4) != "save" || countToken(inputFromUser) != 2)
                {
                 std::cout << "\nInvalid Input\n";
                     std::cout << "> ";
                     ableToAdd = true;
                     std::getline(std::cin, inputFromUser);
                     if (std::cin.eof() == true)
                     {
                         std::cout << "\nGoodbye\n";
                         quitGame = true;
                     }
                }
                else
                {
                    if (countToken(inputFromUser) == 2)
                    {
                        //call saveGame() here
                        saveGame(getNameOfFileFromUserInput(inputFromUser), player, tileBag);
                        std::cout << "\nGame successfully saved\n\n";
                        std::cout << "> ";
                        ableToAdd = true;
                        std::getline(std::cin, inputFromUser);
                        if (std::cin.eof() == true)
                        {
                            std::cout << "\nGoodbye\n";
                            quitGame = true;
                        }
                    }
                }
    }
}

void GameEngine::processLinkedListWhenPlacing(Player* player, LinkedList* tileBag, Tile* newTile)
{
    player->getPlayerHand()->deleteTile(newTile);
    player->getPlayerHand()->addBack(tileBag->getFront());
    tileBag->deleteFront();
}

void GameEngine::printInvalidWhenIllegalMove(bool& ableToAdd, bool& quitGame, std::string& inputFromUser)
{
  if (ableToAdd == false)
  {
        std::cout << "\nInvalid Input\n";
        std::cout << "> ";

        std::getline(std::cin, inputFromUser);
        if (std::cin.eof() == true)
        {
               std::cout << "\nGoodbye\n";
               quitGame = true;
        }
  }
}

void GameEngine::playGame(std::string p1, std::string p2)
{

    //tileBag created inside scope of playGame
    LinkedList *tileBag = new LinkedList();
    LinkedList *firstPlayerHand = new LinkedList();
    LinkedList *secondPlayerHand = new LinkedList();

    Player *firstPlayer = new Player(1, p1, firstPlayerHand);
    Player *secondPlayer = new Player(2, p2, secondPlayerHand);

    addPlayer(firstPlayer);
    addPlayer(secondPlayer);

    bool firstPlayerTurn = true;

    bool repromtFirstPlayer = true;
    bool repromptSecondPlayer = true;

    bool ableToAddTileForPlayer1 = true;
    bool ableToAddTileForPlayer2 = true;

    // Create the tile bag
    shuffleAndCreateTileBag(tileBag);

    setUpTilesInitially(firstPlayer, tileBag);
    setUpTilesInitially(secondPlayer, tileBag);

    std::string inputFromUser = "";
    std::string tileInput = "";
    std::string gridLocation = "";

    int turn = 0;
    bool quitGame = false;

    //game starts here
    do
    {
        if (firstPlayerTurn == true)
        {
            this->getState(firstPlayer);
            std::getline(std::cin, inputFromUser);
            if (std::cin.eof() == true)
            {
                std::cout << "\n\nGoodbye\n";
                quitGame = true;
            }
        }

        //at the start of the game we do not have to check legal move on board
        if (turn == 0 && firstPlayerTurn == true)
        {
            //if player does not quit
            if (quitGame != true)
            {
                //start prompting and validating here
                do
                {
                    //saveGame and invalid input (include invalidformat, invalidtileexistinhand and invalidmove ) goes into here
                    if (validateFormat(inputFromUser) == false || validateTileExistInHand(getTileFromUserInput(inputFromUser), firstPlayer) == false)
                    {
                        //suppose player saves game many times
                        printMessageWhenSaveGame(inputFromUser, firstPlayer, tileBag, quitGame);
                        printMessageWhenInvalidFormat(inputFromUser, firstPlayer, tileBag, quitGame, ableToAddTileForPlayer1);
                    }

                    //after save and invalid input and do not quitGame goes into here for further validation
                    //or input correctly the first time
                    if (quitGame != true)
                    {

                        if (countToken(inputFromUser) == COMMAND_SIZE_WHEN_PLACE_TILE)
                        {

                            tileInput = getTileFromUserInput(inputFromUser);        
                            gridLocation = getLocationFromUserInput(inputFromUser); 

                            if (validateFormat(inputFromUser) == true && validateTileExistInHand(tileInput, firstPlayer) == true)
                            {
                                firstPlayerTurn = false;
                               
                                //turn to c-style string for comparison
                                int size = tileInput.size();
                                char cTileInput[size + 1];
                                strcpy(cTileInput, tileInput.c_str());

                                Tile *newTile = new Tile(cTileInput[0], cTileInput[1] - 48);

                                if (gridLocation.size() == 2)
                                {
                                    int sizeLocation = gridLocation.size();

                                    char cSizeInput[sizeLocation + 1];
                                    strcpy(cSizeInput, gridLocation.c_str());
                                    //cSizeInput[0] = y coordinate, cSizeInput[1] = x
                                    Coordinate c = Coordinate(cSizeInput[0], cSizeInput[1] - 48, *newTile);
                                    board.addTileAt(c);
                                    ableToAddTileForPlayer1 = true;
                                    firstPlayer->setPlayerScore(board.totalPoint(c));
                                    processLinkedListWhenPlacing(firstPlayer, tileBag, newTile);
                                    
                                }
                                else
                                {
                                    int sizeLocation = gridLocation.size();

                                    char cSizeInput[sizeLocation + 1];
                                    strcpy(cSizeInput, gridLocation.c_str());

                                    int x = (cSizeInput[1] - 48) * 10 + (cSizeInput[2] - 48);

                                    //cSizeInput[0] = y coordinate, x = x coordinate
                                    Coordinate c = Coordinate(cSizeInput[0], x, *newTile);
                                    board.addTileAt(c);

                                    firstPlayer->setPlayerScore(board.totalPoint(c));
                                    processLinkedListWhenPlacing(firstPlayer, tileBag, newTile);
                                    ableToAddTileForPlayer1 = true;
                                }

                                delete newTile;
                                turn++;
                                repromtFirstPlayer = false;
                            }
                        }
                        else if (countToken(inputFromUser) == COMMAND_SIZE_WHEN_REPLACE_TILE)
                        {
                            tileInput = getTileFromUserInput(inputFromUser);
                            if (validateFormat(inputFromUser) && validateTileExistInHand(tileInput, firstPlayer))
                            {
                                //pass all the validation for replacing tile

                                firstPlayerTurn = false;

                                int size = tileInput.size();
                                char cTileInput[size + 1];
                                strcpy(cTileInput, tileInput.c_str());

                                Tile *newTile = new Tile(cTileInput[0], cTileInput[1] - 48);


                                tileBag->addBack(newTile);
                                firstPlayer->getPlayerHand()->deleteTile(newTile);
                                firstPlayer->getPlayerHand()->addBack(tileBag->getFront());
                                tileBag->deleteFront();
                                
                                delete newTile;

                                ableToAddTileForPlayer1 = true;
                                turn++;
                                repromtFirstPlayer = false;
                            }
                        }
                    }

                } while ((validateFormat(inputFromUser) == false || validateTileExistInHand(getTileFromUserInput(inputFromUser), firstPlayer) == false) && quitGame != true && repromtFirstPlayer == true && ableToAddTileForPlayer1 == false);
            }
        }
        else if (turn != 0)
        {

            //if player 1 does not want to quitGame start validating input
            if (quitGame != true)
            {
                if (firstPlayerTurn == true)
                {
                    //start prompting player 1 here
                    do
                    {
                        //saveGame goes into this thread
                        if (validateFormat(inputFromUser) == false || validateTileExistInHand(getTileFromUserInput(inputFromUser), firstPlayer) == false || ableToAddTileForPlayer1 == false)
                        {
                            //suppose player saves game many times
                            printMessageWhenSaveGame(inputFromUser, firstPlayer, tileBag, quitGame);
                            printMessageWhenInvalidFormat(inputFromUser, firstPlayer, tileBag, quitGame, ableToAddTileForPlayer1);
                            printInvalidWhenIllegalMove(ableToAddTileForPlayer1, quitGame, inputFromUser);
                            
                        }
                        //player does not quit
                        if (quitGame != true)
                        {

                            if (countToken(inputFromUser) == COMMAND_SIZE_WHEN_PLACE_TILE)
                            {

                                tileInput = getTileFromUserInput(inputFromUser);       
                                gridLocation = getLocationFromUserInput(inputFromUser); 

                                if (validateFormat(inputFromUser) == true && validateTileExistInHand(tileInput, firstPlayer) == true)
                                {

                                    int size = tileInput.size();
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
                                            ableToAddTileForPlayer1 = false;
                                            firstPlayerTurn = true;
                                            repromtFirstPlayer = true;
                                        }
                                        else
                                        {

                                            firstPlayer->setPlayerScore(board.totalPoint(c));
                                            if (board.totalPoint(c) == 12 || board.totalPoint(c) == 24)
                                            {
                                                std::cout << "\nQWIRKLE!!!\n";
                                            }
                                            processLinkedListWhenPlacing(firstPlayer, tileBag, newTile);

                                            ableToAddTileForPlayer1 = true;
                                            firstPlayerTurn = false;
                                            repromtFirstPlayer = false;
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
                                            ableToAddTileForPlayer1 = false;
                                            firstPlayerTurn = true;
                                            repromtFirstPlayer = true;
                                        }
                                        else
                                        {


                                            firstPlayer->setPlayerScore(board.totalPoint(c));
                                            if (board.totalPoint(c) == 12)
                                            {
                                                std::cout << "\nQWIRKLE!!!\n";
                                            }
                                            processLinkedListWhenPlacing(firstPlayer, tileBag, newTile);
                                            ableToAddTileForPlayer1 = true;
                                            firstPlayerTurn = false;
                                            repromtFirstPlayer = false;
                                        }
                                    }
                                    delete newTile;
                                    turn++;
                                }
                            }
                            else if (countToken(inputFromUser) == COMMAND_SIZE_WHEN_REPLACE_TILE)
                            {
                                tileInput = getTileFromUserInput(inputFromUser);
                                if (validateFormat(inputFromUser) && validateTileExistInHand(tileInput, firstPlayer))
                                {
                                   
                                    firstPlayerTurn = false;

                                    int size = tileInput.size();
                                    char cTileInput[size + 1];
                                    strcpy(cTileInput, tileInput.c_str());

                                    Tile *newTile = new Tile(cTileInput[0], cTileInput[1] - 48);

                                    tileBag->addBack(newTile);
                                    firstPlayer->getPlayerHand()->deleteTile(newTile);
                                    firstPlayer->getPlayerHand()->addBack(tileBag->getFront());
                                    tileBag->deleteFront();
                                    delete newTile;
                                    
                                    ableToAddTileForPlayer1 = true;
                                    turn++;
                                    repromtFirstPlayer = false;
                                }
                            }
                        }
                    } while ((validateFormat(inputFromUser) == false || validateTileExistInHand(getTileFromUserInput(inputFromUser), firstPlayer) == false || ableToAddTileForPlayer1 == false) && quitGame != true && repromtFirstPlayer == true);
                }

                //player 2 turn- start prompting player 2 here
                if (quitGame != true && firstPlayerTurn == false)
                {

                    this->getState(secondPlayer);

                    std::getline(std::cin, inputFromUser);
                    if (std::cin.eof())
                    {
                        std::cout << "\nGoodbye\n";
                        quitGame = true;
                    }

                    //if player 2 does not want to quitGame
                    if (quitGame != true)
                    {
                        do
                        {
                            if (validateFormat(inputFromUser) == false || validateTileExistInHand(getTileFromUserInput(inputFromUser), secondPlayer) == false || ableToAddTileForPlayer2 == false)
                            {          
                                printMessageWhenSaveGame(inputFromUser, secondPlayer, tileBag, quitGame);
                                printMessageWhenInvalidFormat(inputFromUser, secondPlayer, tileBag, quitGame, ableToAddTileForPlayer2); 
                                printInvalidWhenIllegalMove(ableToAddTileForPlayer2, quitGame, inputFromUser);
                            }
                            if (quitGame != true)
                            {

                                if (countToken(inputFromUser) == COMMAND_SIZE_WHEN_PLACE_TILE)
                                {

                                    tileInput = getTileFromUserInput(inputFromUser);        
                                    gridLocation = getLocationFromUserInput(inputFromUser); 

                                    if (validateFormat(inputFromUser) == true && validateTileExistInHand(tileInput, secondPlayer))
                                    {

                                        
                                        int size = tileInput.size();
                                        char cTileInput[size + 1];
                                        strcpy(cTileInput, tileInput.c_str());

                                        Tile *newTile = new Tile(cTileInput[0], cTileInput[1] - 48);

                                        //grid location is a two-char A2
                                        if (gridLocation.size() == 2)
                                        {
                                            int sizeLocation = gridLocation.size();

                                            char cSizeInput[sizeLocation + 1];
                                            strcpy(cSizeInput, gridLocation.c_str());
                                            //cSizeInput[0] = y , cSizeInput[1] = x
                                            Coordinate c = Coordinate(cSizeInput[0], cSizeInput[1] - 48, *newTile);

                                            if (!board.addTileAt(c))
                                            {
                                                ableToAddTileForPlayer2 = false;
                                                repromptSecondPlayer = true;
                                                firstPlayerTurn = false;
                                            }
                                            else
                                            {
                                                secondPlayer->setPlayerScore(board.totalPoint(c));
                                                if (board.totalPoint(c) == 12 || board.totalPoint(c) == 24)
                                                {
                                                    std::cout << "\nQWIRKLE!!!\n";
                                                }
                                                processLinkedListWhenPlacing(secondPlayer, tileBag, newTile);

                                                repromptSecondPlayer = false;
                                                firstPlayerTurn = true;
                                                ableToAddTileForPlayer2 = true;
                                            }
                                        }
                                        //grid location is a three-char
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
                                                ableToAddTileForPlayer2 = false;
                                                firstPlayerTurn = false;
                                                repromptSecondPlayer = true;
                                            }
                                            else
                                            {
                                                secondPlayer->setPlayerScore(board.totalPoint(c));
                                                if (board.totalPoint(c) == 12)
                                                {
                                                    std::cout << "\nQWIRKLE!!!\n";
                                                }
                                                processLinkedListWhenPlacing(secondPlayer, tileBag, newTile);

                                                firstPlayerTurn = true;
                                                repromptSecondPlayer = false;
                                                ableToAddTileForPlayer2 = true;
                                            }
                                        }
                                        delete newTile;
                                        turn++;
                                    }
                                }
                                else if(countToken(inputFromUser) == COMMAND_SIZE_WHEN_REPLACE_TILE)
                                {

                                    tileInput = getTileFromUserInput(inputFromUser);
                                    if (validateFormat(inputFromUser) && validateTileExistInHand(tileInput, secondPlayer))
                                    {

                                        int size = tileInput.size();
                                        char cTileInput[size + 1];
                                        strcpy(cTileInput, tileInput.c_str());

                                        Tile *newTile = new Tile(cTileInput[0], cTileInput[1] - 48);
                                        secondPlayer->getPlayerHand()->deleteTile(newTile);
                                        tileBag->addBack(newTile);
                                        secondPlayer->getPlayerHand()->addBack(tileBag->getFront());
                                        tileBag->deleteFront();
                                        delete newTile;

                                        firstPlayerTurn = true;
                                        ableToAddTileForPlayer2 = true;
                                        turn++;
                                        repromptSecondPlayer = false;
                                    }
                                }
                            }

                        } while ((validateFormat(inputFromUser) == false || validateTileExistInHand(getTileFromUserInput(inputFromUser), secondPlayer) == false || ableToAddTileForPlayer2 == false) && quitGame != true && repromptSecondPlayer == true);
                    }
                }
            }
        }

    } while ((tileBag->getSize() != 0 || ((firstPlayer->getPlayerHand()->getSize() != 0) && secondPlayer->getPlayerHand()->getSize() != 0)) && quitGame != true);

    //only display when the game ends not quitGame
    if (quitGame == false)
    {
        std::cout << "Game over\n";
        std::cout << "Score for " << firstPlayer->getPlayerName() << ": " << firstPlayer->getPlayerScore() << std::endl;
        std::cout << "Score for " << secondPlayer->getPlayerName() << ": " << secondPlayer->getPlayerScore() << std::endl;

        if (firstPlayer->getPlayerScore() > secondPlayer->getPlayerScore())
        {
            std::cout << "Player " << firstPlayer->getPlayerScore() << " won!\n";
        }
        else
        {
            std::cout << "Player " << secondPlayer->getPlayerScore() << " won!\n";
        }
        std::cout << "\nGoodbye";
    }

    delete firstPlayerHand;
    delete secondPlayerHand;
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
        delete tileToBeAdded;
    }
}
