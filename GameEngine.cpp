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
//   Board board  = Board();
//   grid = BoardDisplay::makeGrid(board);
//   BoardDisplay::buildGrid(grid,board);
//   tileBag = new LinkedList();

}

GameEngine::~GameEngine(){

//   BoardDisplay::deleteGrid(grid,board);
//   delete tileBag; 
  //error 
//   delete[] playerList;
  
}

void GameEngine::getState(Player* p){
  
  std::cout <<"\n" << p->getPlayerName() << ", it's your turn" << std::endl;
  printScore();
  std::cout << std::endl;

  //print out the board
  //place tile on grid and place tile on board are different 
//   BoardDisplay::placeTile(grid,board);
//   BoardDisplay::printGrid(grid,board);
  std::cout<<"\n\n\n\n\n\n\n\n\n             PRINT BOARD HERE                   \n\n\n\n\n\n\n\n\n";
  std::cout << "\nYour hand is " << std::endl;
  p->displayTileInHand(); 
  
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

// Player* GameEngine::getPlayer(int id){
//   for (int i = 0; i < playerCount; i++){
//     if(playerList[i]->getPlayerId() == id){
//       return playerList[i];
//     }
//   }
//   return NULL;
// }

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

// Board& GameEngine::getBoard()
// {
//   return board;
// }

bool GameEngine::checkFormatForTile(std::string input)
{
    bool result = false;
    
    int size = input.size();

    char char_array[size+1];
    strcpy(char_array, input.c_str());
    
    //tiles are always represented as a two-character of colour and shape
    if(size == 2)
    {
     //three cases for incorrect tile in total only 1 correct tile will pass the validation here
     //three incorrect tile:correct tile/incorrect shape, correct shape/ incorrect tile, incorrect tile/incorrect shape
     if(char_array[0] == RED || char_array[0] == ORANGE || char_array[0] == YELLOW || char_array[0] == GREEN || char_array[0] == BLUE || char_array[0] == PURPLE)
     {

         result = true;


     }
     //ASCII if not from greater than 0 and smaller than 7 then result = false
     //as shape is only represented as 1-6
     if(char_array[1] > 54 || char_array[1] < 48)
     {
         result = false;
     }
    }   
  

    return result; 

}

bool GameEngine::checkFormatForLocation(std::string input)
{
    bool result = false;

    
    int size = input.size();

    char char_array[size+1];

    strcpy(char_array, input.c_str());

    //two-char location e.g:A2
    if(size == 2)
    {
        //A-Z 65-90 ASCII 
        if((char_array[0] > 64 && char_array[0] < 91) && (char_array[1] > 47 && char_array[1] < 58))
        {
            result = true;
        }
    }
    //three-chars location e.g: A15
    else if(size == 3)
    {
        //49  means first digit is 1 - ASCII - e.g: A12 
        //then the second digit can be between 0-9 
        if(char_array[1] == 49)
        {
          if((char_array[0] > 64 && char_array[0] < 91) && char_array[2] > 47 && char_array[2] < 58)
          {
            result = true;
          }
        }
        //50 means first digit is 2 - ASCII - e.g: A21
        //then the second digit can only be between 0-5
        else if(char_array[1] == 50)
        {
          if((char_array[0] > 64 && char_array[0] < 91) && char_array[2] > 47 && char_array[2] < 54)
          {
            result = true;
          }
        }
    }

    return result; 
    
}

bool GameEngine::validateFormat(std::string input)
{
    bool result = false;

    int size = countToken(input);
    std::istringstream token(input);
    std::string firstToken = "";
    std::string secondToken ="";
  
    
    //message size when placing, the format is "place <tile> at <grid location>"
    if(size == 4)
    {
     std::string thirdToken = "";
     std::string fourthToken ="";

     token>>firstToken;
     token>>secondToken;
     token>>thirdToken;
     token>>fourthToken;

     if(firstToken == "place" && checkFormatForTile(secondToken) && thirdToken == "at" && checkFormatForLocation(fourthToken))
     {
         result = true;
     }
    }
    //message size when replacing
    else if(size == 2)
    {
      
        token>>firstToken;
        token>>secondToken;

        if(firstToken == "replace" && checkFormatForTile(secondToken))
        {
            result = true;
        }
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
    Tile* tileToBeCompare = new Tile(char_array[0], char_array[1] - 48);
    if(player->getPlayerHand()->contains(tileToBeCompare))
    {
      result = true;
    }
    return result;   
}


// bool GameEngine::validateMoveLocationExist(std::string inputFromUser, Board& board, Player* player)
// {

//   bool result = true;

//   //message size when placing
// //   if(inputFromUser.size() == 4)
// //   {
// //     std::string gridLocation = "";
    

// //     std::istringstream token(inputFromUser);

// //     //loop to exclude the first three tokens 
// //     for(int i = 0; i < 3; ++i)
// //     {
// //         token>>gridLocation;
// //     }

// //     token>>gridLocation; 


// //     int size = gridLocation.size();

// //     if(size == 2)
// //     {
// //         char char_array[size+1];

// //         strcpy(char_array, gridLocation.c_str());

// //         //coordinate(y, x) A5
// //         Coordinate* coordinate = new Coordinate(char_array[0], char_array[1] - 48);

// //         Tile*  emptyTile = new Tile();

// //         //so at that coordinate there is no tile
// //         if(board.getTileAt(*coordinate).compareTile(emptyTile))
// //         {
// //             result = true;
// //         }

// //     }
// //     //location is a three-char representation 
// //     else
// //     {
// //         char char_array[size+1];

// //         strcpy(char_array, gridLocation.c_str());

// //         int colConverter = (char_array[1] - 48) * 10 + (char_array[2] - 48);

// //         Coordinate* coordinate = new Coordinate(char_array[0], colConverter);

// //         Tile* emptyTile = new Tile();
// //         if(board.getTileAt(*coordinate).compareTile(emptyTile))
// //         {
// //             result = true;
// //         }
// //     }
// //   }
// //   //replace tile case
// //   else if(inputFromUser.size() == 2)
// //   {
// //       if(validateFormat(inputFromUser) && validateTileExistInHand(inputFromUser, player))
// //       {
// //           result = true; 
// //       }
// //   }
  
  
//   return result;
// }



// bool GameEngine::validateLegalMove(std::string tileInput, std::string gridLocation, std::string inputFromUser, Player* player)
// {
//     bool result = true;
//     if(inputFromUser.size() == 2)
//     {
//        if(validateFormat(inputFromUser) && validateTileExistInHand(tileInput, player))
//        {
//            result = true;
//        }
//     }
//     else 
//     {
//         /* code */
//     }

//     return result; 
    
// }

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

  //tileBag created inside scope of playGame 
  LinkedList* tileBag = new LinkedList();
  LinkedList* hand_1 = new LinkedList();
  LinkedList* hand_2 = new LinkedList();


  Player* player_1 = new Player(1, p1, hand_1);
  Player* player_2 = new Player(2, p2, hand_2);

  addPlayer(player_1);
  addPlayer(player_2);
  
  bool playerA = true;
  bool continueLoop = true;

 

  shuffleAndCreateTileBag(tileBag);
   


  setUpTilesInitially(player_1, tileBag);
  setUpTilesInitially(player_2, tileBag);



  

  std::string inputFromUser = "";
  std::string tileInput = ""; 
  std::string gridLocation = ""; 
  
  int turn = 0;
  bool quit = false;
  
  //game starts here
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

void GameEngine::setUpTilesInitially(Player* player, LinkedList* tileBag)
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


