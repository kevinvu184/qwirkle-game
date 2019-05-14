#include "Menu.h"
#include "TileCodes.h"

#include<regex>
#include<iostream>
#include<fstream>
#include<array>
#include<sstream>
#include<string> 
#include <bits/stdc++.h>
#include<algorithm>




#define NUMBER_OF_PLAYERS 2
#define NUMBER_OF_COLOR 6
#define NUMBER_OF_SHAPE 6
#define NUMBER_OF_TILES_IN_PLAYER_HAND 6
#define NUMBER_OF_COMMAS 5 
#define NUMBER_OF_TILES_TOTAL 72
#define LINE_INF_ABOUT_PLAYER 6 

Menu::Menu()
{
    gameEngine = GameEngine();
}

void Menu::runProgram()
{

   int userInput = 0;
   std::string line;

   std::cout << "\n\nWelcome to Qwirkle!" << std::endl;
   std::cout << "-------------------" << std::endl;

    do {
     printMenu();
     std::cin >> userInput;

     // Validate userInput
     if( !(std::cin.eof()) and ((userInput < 1) or (userInput > 4) or (!std::cin)) ){
       std::cin.clear();
       std::cout << "Invalid Input" << std::endl;
     }
     else{
         if ( userInput == 1 ){ 
           remove("records.txt");
           playGame();
         }
         else if( userInput == 2){             
           loadGame();
         }
         else if( userInput == 3){
           showStudentInformation();
         }
         else
         {
           std::cout<<"\nGoodbye\n";
         }
         
       }
     } while ( (std::getline(std::cin, line)) && (userInput != 4) );

   


}

bool Menu::checkForNameInput(std::string name)
{
  bool result = true;

  int size = name.size();

  char cArray[size + 1];

  strcpy(cArray, name.c_str());

  for(int i = 0; i < size && result == true; i++)
  {
    //ASCII A-Z:65-90 , a-z:97-122, space:32  -> different than these then set result = false
    if((cArray[i] < 65 || cArray[i] > 90) && cArray[i] != 32)
    {
      result = false;
    }
  }
  
  return result; 


}

void Menu::playGame()
{
    //read whitespace from previous input before use getline()
    std::cin.ignore();

    std::string p1 = "" ;
    std::string p2 ;

    //to check if it is the initial prompt  
    int count_1 = 0; 
    int count_2 = 0; 

    

    std::cout<<"\nStarting a New Game\n";
    
    do
    {
      if(count_1 == 0)
      {
        std::cout<<"\nEnter a name for player 1 (uppercase characters only)\n";
        std::cout<<"> ";
        
        std::getline(std::cin, p1);
        
      }
      count_1++;
      if(checkForNameInput(p1) == false)
      {
        std::cout<<"\nYour name may contain symbols or numbers or not in uppercase characters, please reenter\n";
        std::cout<<"> ";
        
        std::getline(std::cin, p1);
      }
      
    } while (!checkForNameInput(p1));
    
    do
    {
       if(count_2 == 0)
      {
        std::cout<<"\nEnter a name for player 2 (uppercase characters only)\n";
        std::cout<<"> ";
        std::getline(std::cin, p2);
       
      }
      count_2++;
      if(checkForNameInput(p2) == false)
      {
        std::cout<<"\nYour name may contain symbols or numbers or not in upper case characters, please reenter\n";
        std::cout<<"> ";
        std::getline(std::cin, p2);
     
      }
    } while (!checkForNameInput(p2));  
    
    std::cout<<"\n\nLet's Play!\n\n";
    gameEngine.playGame(p1,p2,1);
    
}

bool Menu::checkFileExist(std::string& fileName)
{
  std::ifstream iffile(fileName.c_str());
  return (bool)iffile;
}

bool Menu::checkFormatForPlayerHand(std::string& playerHand)
{
 
  bool result = true;
  std::vector<std::string> tokens;
  std::string tmp = "";
  std::istringstream input(playerHand);
  
  std::regex tileFormat("([ROYGBP][1-6])");

  int numberOfActualCommas = std::count(playerHand.begin(), playerHand.end(), ',');

  if(numberOfActualCommas == NUMBER_OF_COMMAS)
  {
    while(std::getline(input, tmp, ','))
    {
      //each tokens = tile
      tokens.push_back(tmp);
    }

    for(unsigned int i = 0; i < tokens.size() && result == true; ++i)
    {
      if(std::regex_match(tokens[i], tileFormat) == false)
      {
        result = false;
      }
    }
  }
  else
  {
    result = false;
  }

  
  return result;
  

}

bool Menu::validateFormat(std::string& fileName)
{
  std::ifstream input(fileName);
  bool result = true;

  std::string playerName[NUMBER_OF_PLAYERS];
  int playerScore = 0;
  std::string playerHand = "";
  std::string tileBag = "";
  int numberOfTileInBag = 0;
  int numberOfTileOnBoard = 0;

  std::regex tileFormat("([ROYGBP][1-6])");


  for(int i = 0; i < NUMBER_OF_PLAYERS && result == true; ++i)
  {
    std::getline(input, playerName[i]);

    input>>playerScore;

    //consume whitespace
    input>>std::ws;

    if(input.good())
    {
      
      std::getline(input, playerHand);
      if(checkForNameInput(playerName[i]) == false || checkFormatForPlayerHand(playerHand) == false)
      {
       result = false;
      
      }
    }
    else
    {
      result = false; 
    }
  }
  if(result == true)
  {
    std::string tmp = "";
    std::getline(input, tileBag);

    std::istringstream inString(tileBag);

    while(std::getline(inString, tmp, ',') && result == true)
    {
      if(std::regex_match(tmp, tileFormat) == false)
      {
        result = false;
      }
      else
      {
        numberOfTileInBag++;
      }  
    }
   
    
  }

  if(result == true)
  {
   
    numberOfTileOnBoard = NUMBER_OF_TILES_TOTAL - numberOfTileInBag - NUMBER_OF_PLAYERS*NUMBER_OF_TILES_IN_PLAYER_HAND;

    int countTileOnBoard = 0;

    std::string tmp = "";
    

    while(std::getline(input, tmp) && result == true)
    {
      if(gameEngine.validateFormat(tmp) == false)
      {
        if(tmp != playerName[0] && tmp != playerName[1])
        {
          result = false;
        }
      }
      else
      {
          countTileOnBoard++;
      }
       
    }
   
    if(result == true)
    {
      if(countTileOnBoard != numberOfTileOnBoard)
      {
        result = false;
      }
    }
    
    
  }

  return result;
}

void Menu::keepRecordFileInSyncWithSavingFile(std::string& fileName)
{
  std::ofstream output("records.txt");
  std::ifstream input(fileName);
  bool endOfMove = false;

  std::string tmp = "";
  for(int i = 0; i < 7; i++)
  {
    std::getline(input, tmp);
  }

  while(std::getline(input, tmp) && endOfMove == false)
  {
    if(checkForNameInput(tmp) == true)
    {
      endOfMove = true;
    }
    else
    {
      output<<tmp<<std::endl;
    }
  }
}

void Menu::loadGame()
{

  std::string fileName = "";
  std::vector<std::string> constructPlayerState;
  
  bool load = false;
  bool constructBoardSuccessful = true;
 
  do{
   std::cout<<"\nEnter the filename from which load a game\n";
   std::cout<<"> ";
   std::cin.ignore();
   std::getline(std::cin, fileName);

   while(!checkFileExist(fileName))
   {
     std::cout<<"\nFile does not exist please reenter:\n";
     std::cout<<"> ";
     std::getline(std::cin, fileName);
   }

   if(validateFormat(fileName))
   {
      load = true; 

      std::string tmp = "";
      std::string moves ="";
      std::string tileBag = "";
      std::string playerTurn = "";
      std::ifstream input(fileName);

      for(int i = 0; i < LINE_INF_ABOUT_PLAYER; ++i)
      {
        std::getline(input, tmp);
        constructPlayerState.push_back(tmp);
      }
      
      
      gameEngine.constructPlayerState(constructPlayerState[0], constructPlayerState[1], constructPlayerState[2], constructPlayerState[3], constructPlayerState[4], constructPlayerState[5]);
      input>>tileBag;
    
      gameEngine.forwardTileBag(tileBag);
      input>>std::ws;

      bool continueLoop = true;
      while(std::getline(input, tmp) && continueLoop == true)
      {
        if(tmp != constructPlayerState[0] && tmp != constructPlayerState[3])
        {
          moves.append(tmp);
          moves.append("\n");
        }
        else
        {
          continueLoop = false;
          playerTurn = tmp; 
        }
        
      }
      
      try
      {
        gameEngine.constructBoard(moves);
      }
      catch(const std::exception& e)
      {
        constructBoardSuccessful = false;
        load = false;
      }
      
      if(constructBoardSuccessful == true)
      {
        keepRecordFileInSyncWithSavingFile(fileName);
        std::cout<<"\nQwirkle game successfully loaded !!!\n";
        gameEngine.loadGame(playerTurn, 2);
        
      }
      
      
   }
   else
   {
      std::cout<<"ERROR: Your file name entered has wrong format, cannot load file\n";   
   }
  }while(load == false);
  
}

void Menu::printMenu(){
	std::cout << "Menu\n"
    "1. New Game\n"
	   "2. Load Game\n"
	   "3. Show student information\n"
	   "4. Quit\n"
     "> " << std::flush;
}

void Menu::showStudentInformation(){
  std::cout << "---------------------------------------------" << std::endl;

  std::cout << "Name: Jessica Cruz" << std::endl;
  std::cout << "Student ID: s3571051" << std::endl;
  std::cout << "Email: s3571051@student.rmit.edu.au\n" << std::endl;

  std::cout << "Name: Kevin Vu" << std::endl;
  std::cout << "Student ID: s3678490" << std::endl;
  std::cout << "Email: s3678490@rmit.edu.vn\n" << std::endl;
  std::cout << "Name: Khoi Nguyen" << std::endl;
  std::cout << "Student ID: s3678755" << std::endl;
  std::cout << "Email: s3678755@rmit.edu.vn\n" << std::endl;

  std::cout << "Name: Tuan Vu" << std::endl;
  std::cout << "Student ID: s3678491" << std::endl;
  std::cout << "Email: s3678491@rmit.edu.vn" << std::endl;

  std::cout << "---------------------------------------------\n" << std::endl;
}


