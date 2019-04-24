
#ifndef ASSIGN2_BOARD_H
#define ASSIGN2_BOARD_H

#include "Coordinate.h"
#include "Tile.h"
#include <string>

//Fixed board 26x26
#define INITIAL_COLS 26
#define INITIAL_ROWS 26

class Board {
  private:
    int m_boardSize;
    int m_numOfTile;
    int m_rows;
    int m_cols;

    //Store the board as 2D of Tile
    Tile m_tile[INITIAL_ROWS][INITIAL_COLS];

    //Store possible Coordinate in array
    Coordinate m_coordinate[INITIAL_ROWS * INITIAL_COLS];

  public:
    Board();

    Tile getTileAt(Coordinate& coordinate);
    int getnumOfTile();
    int getBoardSize();
    int getRows();
    int getCols();

    int getRowsCharLength();
    int getColsCharLength();

    void addTile(Tile& tile, Coordinate& coordinate);
    bool containAt(Coordinate& coordinate);
    std::string toString();
};

#endif //ASSIGN2_BOARD_H
