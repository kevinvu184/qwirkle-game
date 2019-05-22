#include "LinkedList.h"
#include "Menu.h"
#include <iostream>
#include <array>
#include<random>
#include <stdlib.h>

#define EXIT_SUCCESS    0

/*
  Deliverables:
  Milestone 1:
    15 Test cases: .input and .output in Test folder.
  Milestone 2:
    Fully functional and error-free (Memory leak error) implementation of basic gameplay.    Fix tile bag by default
  Milestone 3:
   Minor enhancements
    1. Help! in menu section                                                                 Enable by default
    2. Colour tiles when displayed on board                                                  Disable by default
    3. Unicode/Emoji Tile when displayed on board                                            Disable by default
    4. Expandable Board                                                                      Enable by default
    5. High Scores keep record of all time highest score                                     Enable by default
   Major enhancements
    1. Place Multiples Tiles                                                                 Enable by default
 
   NOTE: 1. To get a shuffled tile bag every time playing game, please go into playGame() in GameEngine and uncomment shuffleAndCreateTileBag()
 then comment out method tileBagForUnitTest(). To conduct unit test, just leave the program at its current state.
         2. To enable Colour tiles when displayed on board: uncomment codes from line 55-72 in Tile.cpp
         3. To enable Unicode/Emoji Tile when displayed on board: uncomment codes from line 74-102 in Tile.cpp 

 */
int main(void) {

  Menu menu = Menu();
  menu.runProgram();

  return EXIT_SUCCESS;
}
