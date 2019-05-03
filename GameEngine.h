
#ifndef ASSIGN2_ENGINE_H
#define ASSIGN2_ENGINE_H

#include "Player.h"
#include <string>
#include <iostream>
// #include "Board.h" 
// #include "BoardDisplay.h" 

class GameEngine{
public:
  GameEngine();
  ~GameEngine();
  
  void playGame(std::string p1, std::string p2);

  void addPlayer(Player* p);


  void setUpTilesInitially(Player* player, LinkedList* tileBag);
  void shuffleAndCreateTileBag(LinkedList* tileBag);
  int randomNumberGenerate();

  bool validateFormat(std::string input);
  bool checkFormatForTile(std::string input);
  bool checkFormatForLocation(std::string input);

  std::string getTileFromUserInput(std::string input);
  std::string getLocationFromUserInput(std::string input);

  bool validateTileExistInHand(std::string tileInput, Player* player); 
  // bool validateMoveLocationExist(std::string inputFromUser, Board& board, Player* player);
  bool validateLegalMove(std::string tileInput, std::string gridLocation, std::string inputFromUser, Player* player);
  
  void printScore();
  void scorePoint(Player* p);
  void scoreQwirkle(Player* p);

  void getState(Player* p);
  // Player* getPlayer(int id);
  // Board& getBoard();

  int countToken(std::string);
  


private:
  // Grid grid;
  // Board board;
  Player* playerList[2];
  int playerCount;
  // LinkedList* tileBag; 
};

#endif //ASSIGN2_ENGINE_H