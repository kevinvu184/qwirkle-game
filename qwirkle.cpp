#include "LinkedList.h"
#include "Menu.h"
#include <iostream>
#include <array>
#include<random>
#include <stdlib.h>



#define EXIT_SUCCESS    0

/*
NOTE: 

1) To get a shuffled tile bag every time playing game, please go into playGame() in GameEngine and uncomment shuffleAndCreateTileBag()
then comment out method tileBagForUnitTest(). To conduct unit test, just leave the program at its current state.

2) To get colour and Emoji code, please go into ... 


*/
int main(void) {


  Menu menu = Menu();
  menu.runProgram();

  return EXIT_SUCCESS;
}
