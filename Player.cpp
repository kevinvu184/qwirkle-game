
#include "Player.h"

Player::Player(std::string name){
  this->name = name;
  this->score = 0;
}

Player::~Player(){
  delete hand;
}

std::string Player::getPlayerName(){
  return this->name;
}

int Player::getPlayerScore(){
  return this->score;
}

void Player::setPlayerName(std::string name){
  this->name = name;
}

void Player::setPlayerScore(int score){
  this->score = score;
}

void Player::displayTileInHand(){
  hand->displayList();
}
