
#include "GameEngine.h"

#include <iostream>

GameEngine::GameEngine(){
  this->playerCount = 0;
  g = BoardDisplay::makeGrid(b);
  BoardDisplay::buildGrid(g,b);
}

GameEngine::~GameEngine(){
  this->playerCount = 0;
  BoardDisplay::deleteGrid(g,b);
}

void GameEngine::getState(Player* p){
  std::string input = "";
  std::cout << p->getPlayerName() << ", it's your turn" << std::endl;
  printScore();
  std::cout << std::endl;

  //the printBoard function
  BoardDisplay::placeTile(g,b);
  BoardDisplay::printGrid(g,b);
  std::cout << "\nYour hand is: " << std::endl;
  p->displayTileInHand(); //Seg fault
  std::cout << "\n> ";
  std::cin >> input;
  std::cout << input << std::endl;
}

void GameEngine::play(){

}

void GameEngine::addPlayer(Player* p){
  playerList[playerCount] = p;
  playerCount++;
}

Player* GameEngine::getPlayer(int id){
  for (int i = 0; i < playerCount; i++){
    if(playerList[i]->getPlayerId() == id){
      return playerList[i];
    }
  }
  return NULL;
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
