
#ifndef ASSIGN2_GRID_H
#define ASSIGN2_GRID_H

#include <iostream>
#include "Board.h"

typedef char** Grid;

class Grids {
public:
  Grid makeGrid(Board& b);
  void buildGrid(Grid& grid, Board& b);
  void placeTile(Grid& grid, Board& b);
  void printGrid(Grid grid, Board& b);
  void deleteGrid(Grid grid, Board& b);
};

#endif //ASSIGN2_GRID_H
