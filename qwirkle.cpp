
#include "LinkedList.h"
#include "Player.h"
#include "GameEngine.h"

#include <iostream>

#define EXIT_SUCCESS    0

int main(void) {
   LinkedList* list = new LinkedList();
   delete list;

   GameEngine* game = new GameEngine();
   Player* a = new Player(1,"Khoi");
   game->addPlayer(a);
   game->printState(a);
   game->saveGame("a.txt");
   delete a;
   delete game;
   return EXIT_SUCCESS;
}
