#ifndef ASSIGN_2_PLAYER
#define PLAYER

#include "LinkedList.h"
#include <string>

class Player
{
public:

 Player(std::string name);

 ~Player();

 int getScore();

 LinkedList* getCurrentTilesInPlayerHand();

 std::string displayCurrentTiles();

private:

 int score;

 LinkedList* playerHand;

 std::string name;

};

#endif //ASSIGN_2_PLAYER