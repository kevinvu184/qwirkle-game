#include "Player.h"



Player::Player(std::string name)
{
    score = 0;

    playerHand = new LinkedList();

    this->name = name;


}

Player::~Player()
{
    delete playerHand;
}


int Player::getScore()
{
    return score;
}

LinkedList* Player::getCurrentTilesInPlayerHand()
{
    return playerHand;
}

std::string Player::displayCurrentTiles()
{
    return playerHand->displayList();
}

