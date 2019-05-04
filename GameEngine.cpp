#include "GameEngine.h"
#include "TileCodes.h"


#include<iostream>
#include <array>
#include<random>
#include<sstream>
#include <bits/stdc++.h>

#define MAXIMUM_TILES_BAG 72
#define MAXIMUM_PLAYER_HAND 6
#define NUMBER_OF_COLOR 6
#define NUMBER_OF_SHAPE 6

#include <iostream>

GameEngine::GameEngine(){
  this->playerCount = 0;
}

GameEngine::~GameEngine(){

}

void GameEngine::getState(Player* p){

  std::cout <<"\n" << p->getPlayerName() << ", it's your turn" << std::endl;
  printScore();
  std::cout << std::endl;

  // print out the board
  // @TODO: BoardDisplay::printGrid(grid,board);
  std::cout<<"\n\n\n\n\n\n\n\n\n             PRINT BOARD HERE                   \n\n\n\n\n\n\n\n" << std::endl;

  // place tile on grid and place tile on board are different
  // @TODO: BoardDisplay::placeTile(grid,board);

  // Display the current player's hand
  std::cout << "\nYour hand is " << std::endl;
  p->displayTilesInHand();
  std::cout << "\n> ";
}


int GameEngine::countToken(std::string input)
{
    int count  = 0;

    std::string s1 = "";

    std::istringstream token(input);

    while(token>>s1)
    {
        count++;
    }

    return count;
}


void GameEngine::addPlayer(Player* p){
  playerList[playerCount] = p;
  playerCount++;
}

void GameEngine::printScore(){
  for (int i = 0; i < this->playerCount; i++){
    std::cout << "Score for " << playerList[i]->getPlayerName() << ": " << playerList[i]->getPlayerScore() << std::endl;
  }
}

void GameEngine::scorePoint(Player* p){
  p->setPlayerScore(p->getPlayerScore() + 1);
}

void GameEngine::scoreQwirkle(Player* p){
  p->setPlayerScore(p->getPlayerScore() + 6);
}

bool GameEngine::validateFormat(std::string input)
{
  bool result = false;

  std::regex place ("^place ([ROYGBP][1-6]) at ([A-Z]([1-9]|1[0-9]|2[0-6]))");
  std::regex replace ("^replace ([ROYGBP][1-6])");
  if(std::regex_match(input, place) || std::regex_match(input, replace)){
      result = true;
  }
    return result;
}

bool GameEngine::validateTileExistInHand(std::string tileInput, Player* player)
{
    bool result = false;
    int size = tileInput.size();
    //tile is always a two-char representation
    char char_array[size+1];
    strcpy(char_array, tileInput.c_str());

    //ASCII to convert character into an integer
    Tile* tileToCompare = new Tile(char_array[0], char_array[1] - 48);
    if(player->getPlayerHand()->contains(
    ))
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
    for(int i = 0; i < 1; i++)
    {
        token>>tile;
    }
    token>>tile;


    return tile;
}

std::string GameEngine::getLocationFromUserInput(std::string input)
{
    std::string location ="";


    std::istringstream token(input);

    for(int i = 0; i < 3; i++)
    {
        token>>location;
    }

    token>>location;

    return location;

}

void GameEngine::playGame(std::string p1, std::string p2)
{
  // Declare new objects: tile bag, hands, players...
  LinkedList* tileBag = new LinkedList();
  LinkedList* hand_1 = new LinkedList();
  LinkedList* hand_2 = new LinkedList();

  Player* player_1 = new Player(1, p1, hand_1);
  Player* player_2 = new Player(2, p2, hand_2);
  addPlayer(player_1);
  addPlayer(player_2);

  bool playerA = true;
  bool continueLoop = true;

  // Create the tile bag
  shuffleAndCreateTileBag(tileBag);

  initialisePlayerTiles(player_1, tileBag);
  initialisePlayerTiles(player_2, tileBag);

  std::string inputFromUser = "";
  std::string tileInput = "";
  std::string gridLocation = "";

  int turn = 0;
  bool quit = false;

  // Begin the game
  do{
        if(playerA == true)
        {
          this->getState(player_1);
          std::getline(std::cin, inputFromUser);
          if(std::cin.eof() == true)
          {
             std::cout<<"\n\nGoodbye\n";
             quit = true;
          }
        }

        //at the start of the game we do not have to checkLegalMove() on board
        if(turn == 0 && playerA == true)
        {

            if(quit != true)
            {

                do{

                   //saveGame and invalid input (include invalidformat, invalidtileexistinhand and invalidmove ) goes into here
                    if(validateFormat(inputFromUser) == false || validateTileExistInHand(getTileFromUserInput(inputFromUser), player_1) == false)
                    {
                        //suppose player saves game many times
                       while(inputFromUser.substr(0,4) == "save" && validateFormat(inputFromUser) == false && countToken(inputFromUser) == 2)
                       {
                            //call saveGame() here
                            std::cout<<"\nGame successfully saved\n\n";
                            std::cout<<"> ";

                            //saveGame or Quit(first time input) goes into here
                            std::getline(std::cin, inputFromUser);
                            if(std::cin.eof() == true)
                            {
                                std::cout<<"\nGoodbye\n";
                                quit = true;
                            }
                       }
                       while((validateFormat(inputFromUser) == false || validateTileExistInHand(getTileFromUserInput(inputFromUser), player_1) == false) && quit != true)
                       {
                                if(inputFromUser.substr(0,4) != "save" || countToken(inputFromUser) != 2)
                                {
                                    std::cout<<"\nInvalid Input\n";
                                    std::cout<<"> ";

                                    std::getline(std::cin, inputFromUser);
                                    if(std::cin.eof() == true)
                                    {
                                        std::cout<<"\nGoodbye\n";
                                        quit = true;
                                    }
                                }
                                else
                                {
                                   if(countToken(inputFromUser) == 2)
                                   {
                                    //call saveGame() here
                                    std::cout<<"\nGame successfully saved\n\n";
                                    std::cout<<"> ";

                                    std::getline(std::cin, inputFromUser);
                                    if(std::cin.eof() == true)
                                    {
                                        std::cout<<"\nGoodbye\n";
                                        quit = true;
                                    }
                                   }
                                }
                        }
                    }


                    //after save and invalid input and do not quit goes into here for further validation
                    //or input correctly the first time
                    if(quit != true)
                    {


                        if(countToken(inputFromUser) == 4)
                        {


                            tileInput = getTileFromUserInput(inputFromUser); //get the second element
                            gridLocation = getLocationFromUserInput(inputFromUser); // get the fourth element

                            if(validateFormat(inputFromUser) == true && validateTileExistInHand(tileInput, player_1) == true)
                            {

                                //pass all the validation for placing
                                playerA = false;
                                //board processing
                                // linkedlist processing here
                                int size = tileInput.size();
                                //tile is always a two-char representation
                                char cTileInput[size+1];
                                strcpy(cTileInput, tileInput.c_str());

                                Tile* newTile = new Tile(cTileInput[0],cTileInput[1]-48);
                                player_1->getPlayerHand()->deleteTile(newTile);
                                // board.addTile(newTile);
                                player_1->getPlayerHand()->addBack(tileBag->getFront());
                                tileBag->deleteFront();
                                delete newTile;
                                // update score
                                turn++;
                                continueLoop = false;


                            }

                        }
                        else if(countToken(inputFromUser) == 2)
                        {
                            tileInput = getTileFromUserInput(inputFromUser);
                            if(validateFormat(inputFromUser) && validateTileExistInHand(tileInput, player_1))
                            {
                                //pass all the validation for replacing tile

                                playerA = false;
                                //board processing
                                //linkedlist processing here
                                int size = tileInput.size();
                                //tile is always a two-char representation
                                char cTileInput[size+1];
                                strcpy(cTileInput, tileInput.c_str());

                                Tile* newTile = new Tile(cTileInput[0],cTileInput[1]-48);
                                player_1->getPlayerHand()->deleteTile(newTile);
                                //Place the tile on the board
                                player_1->getPlayerHand()->addBack(tileBag->getFront());
                                tileBag->deleteFront();
                                delete newTile;
                                //update game score
                                turn++;
                                continueLoop = false;
                            }
                        }
                    }

                  }while((validateFormat(inputFromUser) == false || validateTileExistInHand(inputFromUser, player_1) == false) && quit != true && continueLoop == true);
                  //quit != true to reprompt otherwise exit reprompt and end program
                  //validateLocationExist() and validateLegalMove() only apply for placing tile
                  //so we have to have a special case for replacing inside each method implementation
            }
        }
        else if(turn != 0)
        {

          //if player 1 does not want to quit start validating input
          if(quit != true)
          {

             if(playerA == true)
             {
                do{

                      //saveGame goes into this thread
                     if(validateFormat(inputFromUser) == false || validateTileExistInHand(getTileFromUserInput(inputFromUser), player_1) == false)
                     {
                        //suppose player saves game many times
                        while(inputFromUser.substr(0,4) == "save" && validateFormat(inputFromUser) == false && countToken(inputFromUser) == 2)
                        {
                            //call saveGame() here
                            std::cout<<"\nGame successfully saved\n\n";
                            std::cout<<"> ";

                            std::getline(std::cin, inputFromUser);
                            if(std::cin.eof() == true)
                            {
                                std::cout<<"\nGoodbye\n";
                                quit = true;
                            }


                        }
                        while((validateFormat(inputFromUser) == false || validateTileExistInHand(getTileFromUserInput(inputFromUser), player_1) == false )&& quit != true)
                        {
                                if(inputFromUser.substr(0,4) != "save" || countToken(inputFromUser) != 2)
                                {
                                    std::cout<<"\nInvalid Input\n";
                                    std::cout<<"> ";

                                    std::getline(std::cin, inputFromUser);
                                    if(std::cin.eof() == true)
                                    {
                                        std::cout<<"\nGoodbye\n";
                                        quit = true;
                                    }
                                }
                                else
                                {
                                   if(countToken(inputFromUser) == 2)
                                   {
                                    //call saveGame() here
                                    std::cout<<"\nGame successfully saved\n\n";
                                    std::cout<<"> ";

                                    std::getline(std::cin, inputFromUser);
                                    if(std::cin.eof() == true)
                                    {
                                        std::cout<<"\nGoodbye\n";
                                        quit = true;
                                    }
                                   }
                                }

                        }

                    }

                    //invalid two times
                    if(quit != true)
                    {

                        if(countToken(inputFromUser) == 4)
                        {


                            tileInput = getTileFromUserInput(inputFromUser); //get the second element
                            gridLocation = getLocationFromUserInput(inputFromUser); // get the fourth element

                            if(validateFormat(inputFromUser) == true && validateTileExistInHand(tileInput, player_1) == true)
                            {

                                //pass all the validation for placing

                                //board processing here
                                //doing linkedlist processing here
                                int size = tileInput.size();
                                //tile is always a two-char representation
                                char cTileInput[size+1];
                                strcpy(cTileInput, tileInput.c_str());

                                Tile* newTile = new Tile(cTileInput[0],cTileInput[1]-48);
                                player_1->getPlayerHand()->deleteTile(newTile);
                                //Place the tile on the board
                                player_1->getPlayerHand()->addBack(tileBag->getFront());
                                tileBag->deleteFront();
                                delete newTile;
                                //update score
                                turn++;
                                playerA = false;
                                continueLoop = false;

                            }

                        }
                        else if(countToken(inputFromUser) == 2)
                        {
                            tileInput = getTileFromUserInput(inputFromUser);
                            if(validateFormat(inputFromUser) && validateTileExistInHand(tileInput, player_1))
                            {
                                //pass all the validation for replacing

                                playerA = false;

                                //board processing here
                                //doing linkedlist processing here
                                int size = tileInput.size();
                                //tile is always a two-char representation
                                char cTileInput[size+1];
                                strcpy(cTileInput, tileInput.c_str());

                                Tile* newTile = new Tile(cTileInput[0],cTileInput[1]-48);
                                player_1->getPlayerHand()->deleteTile(newTile);
                                //Place the tile on the board
                                player_1->getPlayerHand()->addBack(tileBag->getFront());
                                tileBag->deleteFront();
                                delete newTile;
                                //update score

                                turn++;
                                continueLoop = false;
                            }
                        }
                    }
                }while((validateFormat(inputFromUser) == false || validateTileExistInHand(inputFromUser, player_1) == false)&& quit != true && continueLoop == true);
             }

            //redundant ???? - NO as player 1 save and quit
            //we do not want the game to print out game state for player 2

            if(quit != true && playerA == false)
            {

                this->getState(player_2);

                std::getline(std::cin, inputFromUser);
                if(std::cin.eof())
                {
                    std::cout<<"\nGoodbye\n";
                    quit = true;
                }

                //if player 2 does not want to quit
                if(quit != true)
                {
                    do{
                        if(validateFormat(inputFromUser) == false || validateTileExistInHand(getTileFromUserInput(inputFromUser), player_2) == false)
                        {
                            //suppose player wants to save game many times
                            while(inputFromUser.substr(0,4) == "save" && validateFormat(inputFromUser) == false && countToken(inputFromUser) == 2)
                            {
                               //call saveGame() here
                                std::cout<<"\nGame successfully saved\n\n";
                                std::cout<<"> ";

                                std::getline(std::cin, inputFromUser);
                                if(std::cin.eof())
                                {
                                    quit = true;
                                    std::cout<<"\nGoodbye\n";
                                }
                            }
                            while((validateFormat(inputFromUser) == false || validateTileExistInHand(getTileFromUserInput(inputFromUser), player_2) == false)  && quit != true)
                            {
                                if(inputFromUser.substr(0,4) != "save" || countToken(inputFromUser) != 2)
                                {
                                    std::cout<<"\nInvalid Input\n";
                                    std::cout<<"> ";

                                    std::getline(std::cin, inputFromUser);
                                    if(std::cin.eof() == true)
                                    {
                                        std::cout<<"\nGoodbye\n";
                                        quit = true;
                                    }
                                }
                                else
                                {
                                   if(countToken(inputFromUser) == 2)
                                   {
                                    //call saveGame() here
                                    std::cout<<"\nGame successfully saved\n\n";
                                    std::cout<<"> ";

                                    std::getline(std::cin, inputFromUser);
                                    if(std::cin.eof() == true)
                                    {
                                        std::cout<<"\nGoodbye\n";
                                        quit = true;
                                    }
                                   }
                                }

                            }
                        }
                        if(quit != true)
                        {

                            if(countToken(inputFromUser) == 4)
                            {


                                tileInput = getTileFromUserInput(inputFromUser); //get the second element
                                gridLocation = getLocationFromUserInput(inputFromUser); // get the fourth element

                                if(validateFormat(inputFromUser) == true && validateTileExistInHand(tileInput, player_2))
                                {

                                        //pass all the validation for placing
                                        playerA = true;
                                        //board processing here
                                        //doing linkedlist processing here
                                        int size = tileInput.size();
                                        //tile is always a two-char representation
                                        char cTileInput[size+1];
                                        strcpy(cTileInput, tileInput.c_str());

                                        Tile* newTile = new Tile(cTileInput[0],cTileInput[1]-48);
                                        player_2->getPlayerHand()->deleteTile(newTile);
                                        //Place the tile on the board
                                        player_2->getPlayerHand()->addBack(tileBag->getFront());
                                        tileBag->deleteFront();
                                        delete newTile;
                                        //update score
                                        turn++;
                                        continueLoop = false;
                                }
                            }
                            else
                            {

                                 tileInput = getTileFromUserInput(inputFromUser);
                                 if(validateFormat(inputFromUser) && validateTileExistInHand(tileInput, player_2))
                                 {

                                        //pass all the validation for replacing

                                        //board processing here
                                        //doing linkedlist processing here
                                        int size = tileInput.size();
                                        //tile is always a two-char representation
                                        char cTileInput[size+1];
                                        strcpy(cTileInput, tileInput.c_str());

                                        Tile* newTile = new Tile(cTileInput[0],cTileInput[1]-48);
                                        player_2->getPlayerHand()->deleteTile(newTile);
                                        //Place the tile on the board
                                        player_2->getPlayerHand()->addBack(tileBag->getFront());
                                        tileBag->deleteFront();
                                        delete newTile;
                                        //update game state
                                        playerA = true;


                                    turn++;
                                    continueLoop = false;

                                }
                            }
                        }

                    }while((validateFormat(inputFromUser) == false || validateTileExistInHand(inputFromUser, player_2) == false)&& quit != true && continueLoop == true);
                }
            }
          }

        }

    }  while((tileBag->getSize() != 0 || ((player_1->getPlayerHand()->getSize() != 0) && player_2->getPlayerHand()->getSize() != 0)) && quit != true);

    //only display when the game ends not QUIT
    if(quit == false)
    {
        std::cout<<"Game over\n";
        std::cout<<"Score for "<<player_1->getPlayerName()<<": "<<player_1->getPlayerScore()<<std::endl;
        std::cout<<"Score for "<<player_2->getPlayerName()<<": "<<player_2->getPlayerScore()<<std::endl;

        if(player_1->getPlayerScore() > player_2->getPlayerScore())
        {
            std::cout<<"Player "<<player_1->getPlayerScore()<<" won!\n";
        }
        else
        {
            std::cout<<"Player "<<player_2->getPlayerScore()<<" won!\n";
        }
        std::cout<<"\nGoodbye";
    }

    delete hand_1;
    delete hand_2;
    delete tileBag;


}

void GameEngine::initialisePlayerTiles(Player* player, LinkedList* tileBag)
{
   for(int i = 0; i < MAXIMUM_PLAYER_HAND; ++i)
  {
     player->getPlayerHand()->addBack(tileBag->getFront());
     tileBag->deleteFront();
  }

}

int GameEngine::randomNumberGenerate()
{
   std::random_device rd;
   std::mt19937 eng(rd());
   std::uniform_int_distribution<> distr(0,5);

   return distr(eng);
}


void GameEngine::shuffleAndCreateTileBag(LinkedList* tileBag)
{
   std::array<char, NUMBER_OF_COLOR> colours = {RED, ORANGE, GREEN, BLUE, PURPLE, YELLOW};
   std::array<int, NUMBER_OF_SHAPE> shapes  = {CIRCLE, STAR_4, DIAMOND, SQUARE, STAR_6, CLOVER};

   //the algorithm can be found in linkedlist.cpp
   for(int count = 0; count < MAXIMUM_TILES_BAG; count++)
   {
     Tile* tileToBeAdded = new Tile(colours[randomNumberGenerate()], shapes[randomNumberGenerate()]);
     while(tileBag->tileExist(tileToBeAdded) == 2)
     {
        delete tileToBeAdded;
        tileToBeAdded = new Tile(colours[randomNumberGenerate()], shapes[randomNumberGenerate()]);
     }

     tileBag->addBack(tileToBeAdded);
   }
}
