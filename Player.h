#ifndef ASSIGN2_PLAYER_H
#define ASSIGN2_PLAYER_H

#include "LinkedList.h"
#include <iostream>
#include <string>

class Player {
  public:
    Player(int id, std::string name);
    Player(int id, std::string name, LinkedList* newHand);
    ~Player();

    int getPlayerId();
    std::string getPlayerName();
    int getPlayerScore();
    LinkedList* getPlayerHand();

    void setPlayerId(int id);
    void setPlayerName(std::string name);
    void setPlayerScore(int score);

    void displayTileInHand();

    int id;
    std::string name;
    int score;
    LinkedList* hand;

};

#endif //ASSIGN2_PLAYER_H
