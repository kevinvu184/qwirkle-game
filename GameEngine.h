
#ifndef ASSIGN2_ENGINE_H
#define ASSIGN2_ENGINE_H

#include "Player.h"
#include <string>

class GameEngine{
public:
  GameEngine();
  ~GameEngine();
  std::string getState(Player* p);
  void addPlayer(Player* p);
  void play();
  int getPlayerCount();

  Player* playerList[2];
  int playerCount;
};

#endif //ASSIGN2_ENGINE_H
