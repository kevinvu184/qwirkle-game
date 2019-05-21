#include "Menu.h"
#include "TileCodes.h"
#include <regex>
#include <iostream>
#include <fstream>
#include <array>
#include <sstream>
#include <string>
#include <bits/stdc++.h>
#include <algorithm>

#define NUMBER_OF_PLAYERS 2
#define NUMBER_OF_COLOR 6
#define NUMBER_OF_SHAPE 6
#define NUMBER_OF_TILES_IN_PLAYER_HAND 6
#define NUMBER_OF_COMMAS 5
#define NUMBER_OF_TILES_TOTAL 72
#define LINE_INF_ABOUT_PLAYER 6

#define INVALID "Invalid input."
#define GOODBYE "\nGoodbye\n"
#define ERR_FILE_FORMAT "ERROR: Your file name entered has wrong format, cannot load file."
#define ERR_NAME_FORMAT "Your name must contain uppercase characters only. Please try again."
#define ERR_FILE_NOT_EXIST "ERROR: Your file does not exist, please try again."
#define NUMPLAYERS  2

Menu::Menu()
{
    gameEngine = GameEngine();
}

void Menu::runProgram()
{
   int userInput = 0;
   std::string line;

   std::cout << "\n\nWelcome to Qwirkle!"
    "\n-------------------"<< std::endl;

    do {
     printMenu();
     std::cin >> userInput;

     // Validate userInput
     if( !(std::cin.eof()) and ((userInput < 1) or (userInput > 4) or (!std::cin)) ){
       std::cin.clear();
       std::cout << INVALID << std::endl;
     }
     else{
         if (userInput == 1){
           remove("records.txt");
           playGame();
         }
         else if(userInput == 2){
           loadGame();
         }
         else if(userInput == 3){
           showStudentInformation();
         }
         else
         {
           std::cout << GOODBYE << std::flush;
         }
       }
     } while ( (std::getline(std::cin, line)) && (userInput != 4) );
}

void Menu::playGame()
{
    //clear whitespace from previous input before use getline()
    std::cin.ignore();

    std::string playerNames[NUMPLAYERS];

    std::cout<<"\nStarting a New Game" << std::endl;

    playerNames[0] = inputPlayerNames(1);
    playerNames[1] = inputPlayerNames(2);

    std::cout << "Let's Play!" << std::endl;
    gameEngine.playGame(playerNames[0], playerNames[1], 1); //Need to adjust this for multiplayers
}

bool Menu::validatePlayerName(std::string playerName){
  bool result = false;

  // Only accept UPPERCASE CHARACTERS 1-25 inclusive in length
  std::regex name("[A-Z]{1,25}");
  if(std::regex_match(playerName, name)){
    result = true;
  }
  return result;
}

std::string Menu::inputPlayerNames(int player){
  bool initialPrompt = true;

  std::string playerName = "";

  do{
    if(initialPrompt){
      std::cout << "Please enter a name for player " << player << " (uppercase characters only)" << std::endl;
      std::cout << "> " << std::flush;
      std::getline(std::cin, playerName);
      initialPrompt = false;
    }

    if(!validatePlayerName(playerName)){
      std::cout << ERR_NAME_FORMAT << std::endl;
      std::cout << "> " << std::flush;
      std::getline(std::cin, playerName);
    }
  } while(!validatePlayerName(playerName));
  return playerName;
}

bool Menu::checkFileExist(std::string& fileName) {
  std::ifstream iffile(fileName.c_str());
  return (bool) iffile;
}

bool Menu::checkFormatForPlayerHand(std::string& playerHand) {

  bool result = true;
  std::vector<std::string> tokens;
  std::string tmp = "";
  std::istringstream input(playerHand);
  std::regex tileFormat("([ROYGBP][1-6])");

  while (std::getline(input, tmp, ',')) {
    //each tokens = tile
    tokens.push_back(tmp);
  }

  for (unsigned int i = 0; i < tokens.size() && result == true; ++i) {
    if (std::regex_match(tokens[i], tileFormat) == false) {
      result = false;
    }
  }
  return result;
}

bool Menu::validateFormat(std::string& fileName) {
  std::ifstream input(fileName);
  bool result = true;

  std::string playerName[NUMBER_OF_PLAYERS];
  int playerScore = 0;
  std::string playerHand = "";
  std::string tileBag = "";
  std::regex tileFormat("([ROYGBP][1-6])");

  for(int i = 0; i < NUMBER_OF_PLAYERS && result == true; ++i)
  {
    std::getline(input, playerName[i]);

    input >> playerScore;

    //consume whitespace
    input >> std::ws;

    if (input.good()) {

      std::getline(input, playerHand);
      if (validatePlayerName(playerName[i]) == false
          || checkFormatForPlayerHand(playerHand) == false) {
        result = false;

      }
    } else {
      result = false;
    }
  }

  if (result == true) {
    std::string tmp = "";
    std::getline(input, tileBag);

    std::istringstream inString(tileBag);

    while (std::getline(inString, tmp, ',') && result == true) {
      if (std::regex_match(tmp, tileFormat) == false) {
        result = false;
      }
    }
  }

  if (result == true) {
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
    }
  }

  return result;
}

void Menu::keepRecordFileInSyncWithSavingFile(std::string& fileName) {
  std::ofstream output("records.txt");
  std::ifstream input(fileName);
  bool endOfMove = false;

  std::string tmp = "";
  for (int i = 0; i < 7; i++) {
    std::getline(input, tmp);
  }

  while (std::getline(input, tmp) && endOfMove == false) {
    if (validatePlayerName(tmp) == true) {
      endOfMove = true;
    } else {
      output << tmp << std::endl;
    }
  }
}

void Menu::loadGame() {

  std::string fileName = "";
  std::vector<std::string> constructPlayerState;

  bool load = false;
  bool constructBoardSuccessful = true;

  do{
   std::cout<<"\nEnter the filename of the game you would like to load" << std::endl;
   std::cout<<"> " << std::flush;
   std::getline(std::cin, fileName);

   while(!checkFileExist(fileName))
   {
     std::cout << ERR_FILE_NOT_EXIST << std::endl;
     std::cout<<"> " << std::flush;
     std::getline(std::cin, fileName);
   }

    if(validateFormat(fileName)) {
      load = true;
      std::string tmp = "";
      std::string moves = "";
      std::string tileBag = "";
      std::string playerTurn = "";
      std::ifstream input(fileName);

      for (int i = 0; i < LINE_INF_ABOUT_PLAYER; ++i) {
        std::getline(input, tmp);
        constructPlayerState.push_back(tmp);
      }

      gameEngine.constructPlayerState(constructPlayerState[0],
          constructPlayerState[1], constructPlayerState[2],
          constructPlayerState[3], constructPlayerState[4],
          constructPlayerState[5]);
      input >> tileBag;

      gameEngine.forwardTileBag(tileBag);
      input >> std::ws;

      bool continueLoop = true;
      while (std::getline(input, tmp) && continueLoop == true) {
        if (tmp != constructPlayerState[0] && tmp != constructPlayerState[3]) {
          moves.append(tmp);
          moves.append("\n");
        } else {
          continueLoop = false;
          playerTurn = tmp;
        }
      }

      try
      {
        gameEngine.constructBoard(moves);
        constructBoardSuccessful = true;
      } catch (const std::exception& e) {
        constructBoardSuccessful = false;
        load = false;
      }

      if (constructBoardSuccessful == true) {
        keepRecordFileInSyncWithSavingFile(fileName);
        std::cout << "\nQwirkle game successfully loaded !!!" << std::endl;
        gameEngine.loadGame(playerTurn, 2);

      }
   }
   else
   {
      std::cout << ERR_FILE_FORMAT << std::endl;
   }
  }while(load == false);

}

void Menu::printMenu() {
  std::cout << "Menu\n"
      "1. New Game\n"
      "2. Load Game\n"
      "3. Show student information\n"
      "4. Quit\n"
      "> " << std::flush;
}

void Menu::showStudentInformation() {
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
