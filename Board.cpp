#include "Board.h"

Board::Board() {
  m_numOfTile = 0;
  m_boardSize = 0;
  m_rows = INITIAL_ROWS;
  m_cols = INITIAL_COLS;

  for (int i = 0; i < m_rows; i++) {
    for (int j = 0; j < m_cols; j++) {
      m_tile[i][j] = Tile();
      m_coordinate[m_boardSize] = Coordinate(i, j);
      m_boardSize++;
    }
  }
}

Tile Board::getTileAt(Coordinate& coordinate) {
  return m_tile[coordinate.getX()][coordinate.getY()];
}

void Board::addTile(Tile& tile, Coordinate& coordinate) {
  m_tile[coordinate.getX()][coordinate.getY()] = tile;
  m_numOfTile++;
}

/*
 Convert the Coordinate of the tile in 2D array of Tile
 into the Coordinate in 2D array of char
 for displaying
 */
// + 2 is the first 2 rows in 'displayed board' will be for index (1 .. 26) and '---' dash seperators
// so the coordinate will shift by y + 2
int Board::getRowsCharLength() {
  return m_rows + 2;
}

// * 3 is because each cols in 'displayed board' is 3 char length ( Shape, Colour, '|' seperator)
// + 3 is the index (A .. Z), space and the first '|' seperator
// so the coordinate will shift by x*3 + 3
int Board::getColsCharLength() {
  return m_cols * 3 + 3;
}

bool Board::containAt(Coordinate& coordinate) {
  return m_tile[coordinate.getX()][coordinate.getY()].isExist();
}

int Board::getnumOfTile() {
  return m_numOfTile;
}

int Board::getBoardSize() {
  return m_boardSize;
}

int Board::getRows() {
  return m_rows;
}

int Board::getCols() {
  return m_cols;
}
