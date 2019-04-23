
#include "LinkedList.h"
#include "Player.h"
#include "GameEngine.h"

#include <iostream>

#define EXIT_SUCCESS    0

int main(void) {
   LinkedList* list = new LinkedList();
   delete list;

   std::cout << "Welcome to Qwirkle!" << std::endl;
   std::cout << "-------------------" << std::endl;

   GameEngine* game = new GameEngine();
   Player* a = new Player(1,"Khoi");
   game->addPlayer(a);
   game->getState(a);
   delete a;
   delete game;
   return EXIT_SUCCESS;
}
