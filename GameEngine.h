
#ifndef ASSIGN2_ENGINE_H
#define ASSIGN2_ENGINE_H

#include "Player.h"
#include <string>
#include <iostream>

class GameEngine{
public:
  GameEngine();
  ~GameEngine();
  void getState(Player* p);
  void addPlayer(Player* p);
  void play();
  Player* getPlayer(int id);
  void printScore();

  Player* playerList[2];
  int playerCount;
};

#endif //ASSIGN2_ENGINE_H
