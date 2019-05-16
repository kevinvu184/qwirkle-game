#include "GameEngine.h"
#include "TileCodes.h"

#include <array>
#include <bits/stdc++.h>
#include <iostream>
#include <random>
#include <sstream>
#include <stdexcept>

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
    tileBagStr = "";

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
  outFile << tileBag->displayList() << std::endl;
  outFile<<getRecords();
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
                    std::cout << "\n\nGoodbye\n";
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
                    if(validateFormat(inputFromUser) == false)
                    {
                        std::cout << "\nInvalid Input, Please check your format again\n";
                       
                    }
                    else if(validateTileExistInHand(inputFromUser, player) == false)
                    {
                        std::cout<<"\nInvalid Input, tile input does not exist in your hand\n";
                    }
                   
                     std::cout << "> ";
                     ableToAdd = true;
                     
                     std::getline(std::cin, inputFromUser);
                     if (std::cin.eof() == true)
                     {
                         std::cout << "\n\nGoodbye\n";
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
                            std::cout << "\n\nGoodbye\n";
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
        std::cout << "\nInvalid Input, Please check your move on the board\n";
        std::cout << "> ";

        std::getline(std::cin, inputFromUser);
        if (std::cin.eof() == true)
        {
               std::cout << "\n\nGoodbye\n";
               quitGame = true;  
        }
  }
}

void GameEngine::keepRecords(std::string inputFromUser){
  std::ofstream outFile;
  outFile.open("records.txt", std::ofstream::app);
  outFile << inputFromUser << std::endl;
  outFile.close();
}

std::string GameEngine::getRecords(){
  std::string allMoves = "";
  std::ifstream file("records.txt");

  if (file.is_open()){
    std::string line = "";
    while (std::getline(file, line)){
      allMoves.append(line);
      allMoves.append("\n");
    }
  }
  return allMoves;
}

void GameEngine::constructPlayerState(std::string& firstPlayerName, std::string& scoreFirstPlayer, std::string& firstPlayerHand, std::string& secondPlayerName, std::string& scoreSecondPlayer, std::string& secondPlayerHand)
{
    int score_1 = 0;
    int score_2 = 0;
    
    std::string tmp = "";
    std::istringstream inputPlayerHand_1(firstPlayerHand);

    Player* firstPlayer = new Player(1, firstPlayerName);
    while(std::getline(inputPlayerHand_1, tmp,','))
    {
        char cTileArray[3];
        strcpy(cTileArray, tmp.c_str());
        Tile* tileToBeAdded = new Tile(cTileArray[0], cTileArray[1] - 48);
        firstPlayer->getPlayerHand()->addBack(tileToBeAdded);
        delete tileToBeAdded;
    }

    std::istringstream inputPlayerHand_2(secondPlayerHand);
    Player* secondPlayer = new Player(2, secondPlayerName);
    while(std::getline(inputPlayerHand_2, tmp,','))
    {
        char cTileArray[3];
        strcpy(cTileArray, tmp.c_str());
        Tile* tileToBeAdded = new Tile(cTileArray[0], cTileArray[1] - 48);
        secondPlayer->getPlayerHand()->addBack(tileToBeAdded);
        delete tileToBeAdded;
    }
    
    std::istringstream input_1(scoreFirstPlayer);
    input_1>>score_1;
    std::istringstream input_2(scoreSecondPlayer);
    input_2>>score_2;

    firstPlayer->setPlayerScore(score_1);
    secondPlayer->setPlayerScore(score_2);

    addPlayer(firstPlayer);
    addPlayer(secondPlayer);    

   
}

void GameEngine::forwardTileBag(std::string& tileBagStr)
{
    this->tileBagStr = tileBagStr;
}

LinkedList* GameEngine::constructTileBag(std::string& tileBag)
{
    LinkedList* tileBagList = new LinkedList();

    std::istringstream inString(tileBag);
    std::string tmp = "";
    
    while(std::getline(inString, tmp, ','))
    {
        int size = 0; 
        size = tmp.size();
        char cArray[size + 1];
        strcpy(cArray, tmp.c_str());

        Tile* tileToBeAdded = new Tile(cArray[0], cArray[1] - 48);
        tileBagList->addBack(tileToBeAdded);
        delete tileToBeAdded;
    }
    
    return tileBagList;

}

void GameEngine::constructBoard(std::string& moves)
{
    std::string allMove = moves; 
    

    std::string oneMove = "";
    std::istringstream input(allMove);
    bool firstMove = true;

    while(std::getline(input, oneMove))
    {
       
        std::string tileInput = getTileFromUserInput(oneMove);
        std::string location = getLocationFromUserInput(oneMove);

        char cTileArray[3];
        strcpy(cTileArray, tileInput.c_str());
        Tile* newTile = new Tile(cTileArray[0], cTileArray[1] - 48);

        if(firstMove == true)
        {   
            int sizeLocation = location.size();
            if(sizeLocation == 2)
            {
                char cLocationArray[sizeLocation + 1];
                strcpy(cLocationArray, location.c_str());
                Coordinate c = Coordinate(cLocationArray[0], cLocationArray[1] - 48, *newTile);
                board.addTileAt(c);
            }
            else
            {
                char cLocationArray[sizeLocation + 1];
                strcpy(cLocationArray, location.c_str());
                int xCoordinate = (cLocationArray[1] - 48) * 10 + (cLocationArray[2] - 48);
                Coordinate c = Coordinate(cLocationArray[0], xCoordinate, *newTile);
                board.addTileAt(c);
            }
            firstMove = false;
            // add move to recordFile
            
            
        }
        else
        {
            
            int sizeLocation = location.size();
            if(sizeLocation == 2)
            {
                char cLocationArray[sizeLocation + 1];
                strcpy(cLocationArray, location.c_str());
                Coordinate c = Coordinate(cLocationArray[0], cLocationArray[1] - 48, * newTile);
                
                if(!board.addTileAt(c))
                {
                    throw  std::runtime_error("ERROR: Your file name entered has wrong format, cannot load file\n");
                }
                
            }
            else
            {
                char cLocationArray[sizeLocation + 1];
                strcpy(cLocationArray, location.c_str());
                int xCoordinate = (cLocationArray[1] - 48) * 10 + (cLocationArray[2] - 48);
                Coordinate c = Coordinate(cLocationArray[0], xCoordinate, *newTile);
                if(!board.addTileAt(c))
                {
                    throw std::runtime_error("ERROR: Your file name entered has wrong format, cannot load file\n");
                }
            }
        }
        
            
        delete newTile; 
    }
    
}

void GameEngine::askingForPlacingMultipleTiles(bool& ableToAddTile, bool& firstPlayerTurn, bool& repromptPlayer, bool& quitGame, Player* player, LinkedList* tileBag)
{
    bool passTurn = false;
    bool printState = true;
    std::string inputFromUser ="";

    do{
        if(printState == true)
        {
            getState(player);
            std::getline(std::cin, inputFromUser);
        }
    
        if(inputFromUser == "pass")
        {
            ableToAddTile = true;
            repromptPlayer = false;
            if(player->getPlayerId() == 1)
            {
                firstPlayerTurn = false;
            }
            passTurn = true;
        }
        else if(std::cin.eof() == true)
        {
            std::cout<<"\n\nGoodbye\n";
            passTurn = true;
            quitGame = true;
        }
        else
        {
          
          if(validateFormat(inputFromUser) == false || validateTileExistInHand(getTileFromUserInput(inputFromUser),player) == false || ableToAddTile == false)
          {
              if(validateFormat(inputFromUser) == false)
              {
                if(countToken(inputFromUser) == 2 && inputFromUser.substr(0,4) == "save")
                {
                    std::cout<<"\nGame successfully saved\n";
                    std::string filename = getNameOfFileFromUserInput(inputFromUser);
                    saveGame(filename, player, tileBag);
                    std::cout<<"> ";

                    std::getline(std::cin, inputFromUser);
                } 
                else{ 
                    std::cout<<"Invalid Input, please check your format\n";
                    std::cout<<"> ";
                    std::getline(std::cin, inputFromUser);
                }
              }
              else if(validateTileExistInHand(getTileFromUserInput(inputFromUser), player) == false)
              {
                std::cout<<"Invalid Input, no tile from hand \n";
                std::cout<<"> ";
                std::getline(std::cin, inputFromUser);
              }
              else if(ableToAddTile == false)
              {
                std::cout<<"Invalid Input, please check your move board\n";
                std::cout<<"> ";
                std::getline(std::cin, inputFromUser);
                ableToAddTile = true;
              }
              
              printState = false;
          }else{
        
            if(countToken(inputFromUser) == COMMAND_SIZE_WHEN_PLACE_TILE)
            {
                
                std::string tileInput = getTileFromUserInput(inputFromUser);
                std::string gridLocation = getLocationFromUserInput(inputFromUser);
                if(validateFormat(inputFromUser) == true && validateTileExistInHand(tileInput, player) == true)
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
                                ableToAddTile = false;
                                repromptPlayer = true;
                                if(player->getPlayerId() == 2)
                                {
                                    firstPlayerTurn = false;
                                }
                                printState = false;
                            }
                            else
                            {
                            
                                player->setPlayerScore(board.totalPoint(c));
                                if (board.totalPoint(c) == 12 || board.totalPoint(c) == 24)
                                {
                                       std::cout << "\nQWIRKLE!!!\n";
                                }
                                processLinkedListWhenPlacing(player, tileBag, newTile);

                                repromptPlayer = false;
                                if(player->getPlayerId() == 2)
                                {
                                    firstPlayerTurn = true;
                                }
                                ableToAddTile = true;
                                printState = true;
                                keepRecords(inputFromUser);
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
                            ableToAddTile = false;
                            if(player->getPlayerId() == 2)
                            {
                                firstPlayerTurn = false;
                            }
                            repromptPlayer = true;
                            printState = false;
                        }
                        else
                        {
                            player->setPlayerScore(board.totalPoint(c));
                            if (board.totalPoint(c) == 12)
                            {
                                std::cout << "\nQWIRKLE!!!\n";
                            }
                            processLinkedListWhenPlacing(player, tileBag, newTile);
                            if(player->getPlayerId() == 2)
                            {
                                firstPlayerTurn = true;
                            }
                            repromptPlayer = false;
                            ableToAddTile = true;  
                            printState = true;
                            keepRecords(inputFromUser);
                        }
                    }
                }
             }
             else
             {
                 printState = false;
                 std::cout<<"\nInvalid Input, you can only continue place tile\n\n";
                 std::cout<<">";
                 std::getline(std::cin, inputFromUser);
             }
             
          }
        }
    }while(passTurn == false);
}

void GameEngine::playGame(std::string p1, std::string p2, int selection)
{

    
        //tileBag created inside scope of playGame
        LinkedList* tileBag = nullptr;
        LinkedList* firstPlayerHand = new LinkedList();
        LinkedList* secondPlayerHand = new LinkedList();

        bool firstPlayerTurn = true;
        bool repromtFirstPlayer = true;
        bool repromptSecondPlayer = true;
        bool ableToAddTileForPlayer1 = true;
        bool ableToAddTileForPlayer2 = true;
        bool quitGame = false;
        
        Player* firstPlayer =nullptr;
        Player* secondPlayer= nullptr;

        std::string inputFromUser = "";
        std::string tileInput = "";
        std::string gridLocation = "";

        int turn = 0;
    if(selection == 1)
    {
        tileBag = new LinkedList();
        firstPlayer = new Player(1, p1, firstPlayerHand);
        secondPlayer = new Player(2, p2, secondPlayerHand);

        addPlayer(firstPlayer);
        addPlayer(secondPlayer);
       
       // Create the tile bag
        shuffleAndCreateTileBag(tileBag);

        setUpTilesInitially(firstPlayer, tileBag);
        setUpTilesInitially(secondPlayer, tileBag);
    }
    else if(selection == 2)
    {
        
        tileBag = this->constructTileBag(tileBagStr);
 
        
        if(p1 == playerList[0]->getPlayerName())
        {
            firstPlayerTurn = true;
        }
        else if(p1 == playerList[1] -> getPlayerName())
        {
            firstPlayerTurn = false;
        }
        
       
        turn++;
        firstPlayer = playerList[0];
        secondPlayer = playerList[1];
        
    }
        
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
                                    keepRecords(inputFromUser);
                                    askingForPlacingMultipleTiles(ableToAddTileForPlayer1, firstPlayerTurn, repromtFirstPlayer, quitGame, firstPlayer, tileBag);
                                    
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
                                    keepRecords(inputFromUser);
                                    askingForPlacingMultipleTiles(ableToAddTileForPlayer1, firstPlayerTurn, repromtFirstPlayer, quitGame, firstPlayer, tileBag);
                                }
                                //askToPlaceMultipleTiles() list of parameter and pass to end method remember still to validate invalid input here 

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
                                            keepRecords(inputFromUser);


                                            ableToAddTileForPlayer1 = true;
                                            firstPlayerTurn = false;
                                            repromtFirstPlayer = false;
                                            askingForPlacingMultipleTiles(ableToAddTileForPlayer1, firstPlayerTurn, repromtFirstPlayer, quitGame, firstPlayer, tileBag);

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
                                            keepRecords(inputFromUser);
                                            askingForPlacingMultipleTiles(ableToAddTileForPlayer1, firstPlayerTurn, repromtFirstPlayer, quitGame, firstPlayer, tileBag);
                                            
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
                        std::cout << "\n\nGoodbye\n";
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
                                                keepRecords(inputFromUser);
                                                askingForPlacingMultipleTiles(ableToAddTileForPlayer2, firstPlayerTurn, repromptSecondPlayer, quitGame, secondPlayer, tileBag);
                                                
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
                                                keepRecords(inputFromUser);
                                                askingForPlacingMultipleTiles(ableToAddTileForPlayer2, firstPlayerTurn, repromptSecondPlayer, quitGame, secondPlayer, tileBag);

                                                
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
        std::cout << "\n\nGoodbye";
    }

    delete firstPlayerHand;
    delete secondPlayerHand;
    delete tileBag;
    
    if(selection == 2)
    {
        delete firstPlayer;
        delete secondPlayer;
    }
}

void GameEngine::loadGame(std::string& playerTurn, int selection)
{
    this->playGame(playerTurn, playerTurn, 2);
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
