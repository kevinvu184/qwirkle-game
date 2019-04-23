
#include <string>
#include <iostream>

#include "GameEngine.h"

GameEngine::GameEngine(){
  this->playerCount = 0;
}

GameEngine::~GameEngine(){
  for (int i = 0; i < playerCount; i++){
    delete playerList[i];
  }
}

std::string GameEngine::getState(Player* p){
  std::string display = "";
  return display;
}

void GameEngine::play(){

}

void GameEngine::addPlayer(Player* p){
  playerList[playerCount] = p;
  playerCount++;
}

int GameEngine::getPlayerCount(){
  return playerCount;
}
