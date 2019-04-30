
#include "GameEngine.h"

GameEngine::GameEngine(){
  this->playerCount = 0;
  b = new Board();
  g = BoardDisplay::makeGrid(*b);
  BoardDisplay::buildGrid(g,*b);
  tileBag = new LinkedList();
}

GameEngine::~GameEngine(){
  BoardDisplay::deleteGrid(g,*b);
  delete b;
}

void GameEngine::saveGame(std::string filename, Player* player){
  std::ofstream outFile;
  outFile.open(filename);
  for (int i = 0; i < this->playerCount; i++){
    outFile << playerList[i]->getPlayerName() << std::endl;
    outFile << playerList[i]->getPlayerScore() << std::endl;
    outFile << playerList[i]->displayTileInHand() << std::endl;
  }
  for (int i = 0; i < b->getRowsCharLength(); i++) {
    for (int j = 0; j < b->getColsCharLength(); j++) {
      outFile << g[i][j];
    }
    outFile << "\n";
  }
  //Need Tile bag
  outFile << tileBag->displayList() << std::endl;
  //Display Turn
  outFile << player->getPlayerName()<< std::endl;

}

void GameEngine::printState(Player* p){
  std::cout << p->getPlayerName() << ", it's your turn" << std::endl;
  printScore();
  std::cout << std::endl;

  //the printBoard function
  BoardDisplay::placeTile(g,*b);
  BoardDisplay::printGrid(g,*b);
  std::cout << "\nYour hand is: " << std::endl;
  std::cout << p->displayTileInHand() << std::endl;
  std::cout << "\n> ";
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

void GameEngine::scorePoint(Player* p, int point){
  p->setPlayerScore(p->getPlayerScore() + point);
}
