
#ifndef ASSIGN2_BOARDDISPLAY_H
#define ASSIGN2_BOARDDISPLAY_H

#include <iostream>
#include "Board.h"

typedef char** Grid;

namespace BoardDisplay {
  Grid makeGrid(Board& b);
  void buildGrid(Grid& grid, Board& b);
  void placeTile(Grid& grid, Board& b);
  void printGrid(Grid grid, Board& b);
  void deleteGrid(Grid grid, Board& b);
};

#endif //ASSIGN2_BOARDDISPLAY_H
