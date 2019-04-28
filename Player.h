
#ifndef ASSIGN2_PLAYER_H
#define ASSIGN2_PLAYER_H

#include "LinkedList.h"
#include <iostream>
#include <string>

class Player {
public:
    Player(int id, std::string name);
    ~Player();

    int getPlayerId();
    std::string getPlayerName();
    int getPlayerScore();

    void setPlayerId(int id);
    void setPlayerName(std::string name);
    void setPlayerScore(int score);

    std::string displayTileInHand();

private:
    int id;
    std::string name;
    int score;
    LinkedList* hand;

};

#endif //ASSIGN2_PLAYER_H
