
#include "LinkedList.h"
#include "Player.h"

#include <iostream>

#define EXIT_SUCCESS    0

int main(void) {
   LinkedList* list = new LinkedList();
   delete list;

   std::cout << "Welcome to Qwirkle!" << std::endl;
   std::cout << "-------------------" << std::endl;

   Player* a = new Player("Khoi");
   delete a;
   return EXIT_SUCCESS;
}
