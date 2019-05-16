
#ifndef ASSIGN2_ENGINE_H
#define ASSIGN2_ENGINE_H

#include "Board.h"
#include "Player.h"
#include <iostream>
#include <regex>
#include <string>

class GameEngine
{
public:
  GameEngine();
  ~GameEngine();

  void playGame(std::string p1, std::string p2, int selection);

  void addPlayer(Player *p);

  void setUpTilesInitially(Player *player, LinkedList *tileBag);
  void shuffleAndCreateTileBag(LinkedList *tileBag);
  int randomNumberGenerate();

  bool validateFormat(std::string input);

  std::string getTileFromUserInput(std::string input);
  std::string getLocationFromUserInput(std::string input);

  bool validateTileExistInHand(std::string tileInput, Player *player);
  
  bool validateLegalMove(std::string tileInput, std::string gridLocation, std::string inputFromUser, Player *player);

  void printScore();
  void scorePoint(Player *p);
  void scoreQwirkle(Player *p);

  void getState(Player *p);

  int countToken(std::string);

  void saveGame(std::string filename, Player* player, LinkedList* tileBag);
  std::string getNameOfFileFromUserInput(std::string input);

  void printMessageWhenSaveGame(std::string& inputFromUser,Player* player, LinkedList* tileBag, bool& quitGame);
  void printMessageWhenInvalidFormat(std::string& inputFromUser, Player* player, LinkedList* tileBag, bool& quitGame, bool& ableToAdd);
  void printInvalidWhenIllegalMove(bool& ableToAdd, bool& quitGame, std::string& inputFromUser);

  void processLinkedListWhenPlacing(Player* player, LinkedList* tileBag, Tile* newTile);

  void constructPlayerState(std::string& firstPlayerName, std::string& scoreFirstPlayer, std::string& firstPlayerHand, std::string& secondPlayerName, std::string& scoreSecondPlayer, std::string& secondPlayerHand);
  LinkedList* constructTileBag(std::string& tileBag);
  void forwardTileBag(std::string& tileBagStr);

  void constructBoard(std::string& moves);
  void loadGame(std::string& playerTurn, int selection);

  void keepRecords(std::string inputFromUser);
  std::string getRecords();

  void askingForPlacingMultipleTiles(bool& ableToAddTile, bool& firstPlayerTurn, bool& repromptPlayer, bool& quitGame, Player* player, LinkedList* tileBag);



private:
  Board board;
  Player *playerList[2];
  int playerCount;
  std::string tileBagStr;
  
};

#endif //ASSIGN2_ENGINE_H
