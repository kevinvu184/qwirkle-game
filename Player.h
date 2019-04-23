
#ifndef ASSIGN2_PLAYER_H
#define ASSIGN2_PLAYER_H

#include "LinkedList.h"
#include <iostream>
#include <string>

class Player {
public:
    Player(std::string name);
    ~Player();

    std::string getPlayerName();
    int getPlayerScore();

    void setPlayerName(std::string name);
    void setPlayerScore(int score);

    void displayTileInHand();

    std::string name;
    int score;
    LinkedList* hand;

};

#endif //ASSIGN2_PLAYER_H
