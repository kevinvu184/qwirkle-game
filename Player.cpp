#include "Player.h"

Player::Player(int id, std::string name) {
  this->id = id;
  this->name = name;
  this->score = 0;
  this->hand = new LinkedList();
}

Player::Player(int id, std::string name, LinkedList *newHand) {
  this->id = id;
  this->name = name;
  this->score = 0;
  this->hand = newHand;
}

Player::Player(std::string name)
{
  this->name = name;
  this->score = 0;
}


Player::~Player() {
  //  delete hand;
}

std::string Player::getPlayerName() {
  return this->name;
}

int Player::getPlayerScore() {
  return this->score;
}

LinkedList *Player::getPlayerHand() {
  return hand;
}

void Player::setPlayerName(std::string name) {
  this->name = name;
}

void Player::setPlayerScore(int score) {
  this->score += score;
}

void Player::setUpPlayerScore(int score) {
  this->score = score;
}

void Player::displayTileInHand() {

  std::cout << hand->displayList() << std::endl;
}

void Player::setPlayerId(int id) {
  this->id = id;
}

int Player::getPlayerId() {
  return this->id;
}
