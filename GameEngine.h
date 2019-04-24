
#ifndef ASSIGN2_ENGINE_H
#define ASSIGN2_ENGINE_H

#include "Player.h"
#include <string>
#include <iostream>
#include "Board.h" //Need Board Object
#include "BoardDisplay.h" //Need makeGrid()

class GameEngine{
public:
  GameEngine();
  ~GameEngine();
  void getState(Player* p);
  void addPlayer(Player* p);
  void play();
  Player* getPlayer(int id);
  void printScore();
  void scorePoint(Player* p);
  void scoreQwirkle(Player* p);

  Grid g;
  Board b;
  Player* playerList[2];
  int playerCount;
};

#endif //ASSIGN2_ENGINE_H
