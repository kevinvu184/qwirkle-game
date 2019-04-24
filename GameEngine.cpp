
#include "GameEngine.h"

#include <iostream>

GameEngine::GameEngine(){
  this->playerCount = 0;
}

GameEngine::~GameEngine(){
  // for (int i = 0; i < playerCount; i++){
  //   delete playerList[i];
  // }
  this->playerCount = 0;
}

void GameEngine::getState(Player* p){
  std::string input = "";
  std::cout << p->getPlayerName() << ", it's your turn" << std::endl;
  printScore();
  //I need the Board function here
  Grid grid = g.makeGrid(b);
  g.buildGrid(grid, b);
  g.placeTile(grid, b);
  g.printGrid(grid,b);
  std::cout << "\nYour hand is: " << std::endl;
  // p->displayTileInHand(); //Seg fault
  std::cout << "\n>";
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
