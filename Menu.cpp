#include "Menu.h"
#include <iostream>
#include <fstream>
#include <array>
#include <sstream>
#include <string>
#include <regex>
#include <bits/stdc++.h>

#define INVALID "Invalid input."
#define GOODBYE "\nGoodbye\n"
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
         if(userInput == 1){
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

    // for(int i = 0; i < NUMPLAYERS; i++){
    //   playerNames[i] = inputPlayerNames(i+1);
    // }
    playerNames[0] = inputPlayerNames(1);
    playerNames[1] = inputPlayerNames(2);

    std::cout << "Let's Play!" << std::endl;
    gameEngine.playGame(playerNames[0], playerNames[1]); //Need to adjust this for multiplayers
}

std::string Menu::inputPlayerNames(int player){
  bool validatePlayerName(std::string playerName);
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
      std::cout << "\nYour name must contain uppercase characters only. Please try again." << std::endl;
      std::cout << "> " << std::flush;
      std::getline(std::cin, playerName);
    }
  } while(!validatePlayerName(playerName));
  return playerName;
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

void Menu::loadGame()
{
  //call loadGame in GameEngine here
  //gameEngine.loadGame();

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
