
#ifndef ASSIGN2_ENGINE_H
#define ASSIGN2_ENGINE_H

#include "Player.h"
#include <string>
#include <array>
#include <fstream>
#include <iostream>
#include "Board.h"
#include "BoardDisplay.h"

class GameEngine{
public:
  GameEngine();
  ~GameEngine();
  void printState(Player* p);
  // std::string getInput(); ??
  // bool verify(std::string input);
  // bool validateFormat(std::string input);
  void saveGame(std::string filename, Player* player);
  void addPlayer(Player* p);
  void play();
  Player* getPlayer(int id);
  void printScore();
  void scorePoint(Player* p,int point);

private:
  Grid g;
  Board* b;
  Player* playerList[2]; // std::array
  // std::array<Player*,2> playerList;
  int playerCount;
  LinkedList* tileBag;
};

#endif //ASSIGN2_ENGINE_H
