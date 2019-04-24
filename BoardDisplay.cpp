
#include "BoardDisplay.h"

//Create a 2D array of char for displaying
Grid BoardDisplay::makeGrid(Board& b) {
  Grid grid = NULL;
  if (b.getRowsCharLength() >= 0 && b.getColsCharLength() >= 0) {
    grid = new char*[b.getRowsCharLength()];
    for (int i = 0; i != b.getRowsCharLength(); ++i) {
      grid[i] = new char[b.getColsCharLength()];
    }
  }
  return grid;
}

//Build the layout of the board (rows index, cols index, '|', '---', space)
//This will be refactor in future update
void BoardDisplay::buildGrid(Grid& grid, Board& b) {
  int initialColsCoordinateOfFirstDigit = 3;
  int initialColsCoordinateOfSecondDigit = 4;
  int initialColsCoordinateOfDashSeperator = 2;
  int firstDigit = 48;
  int secondDigit = 48;
  for (int i = 0; i < b.getRowsCharLength(); i++)
    for (int j = 0; j < b.getColsCharLength(); j++)
      //First digits of the cols index (1..26) will be ' ' if index < 10, 1 if index from 10-19, 2 if index 20-26
      if (i == 0 && j == initialColsCoordinateOfSecondDigit) {
        grid[i][j] = secondDigit;
        initialColsCoordinateOfSecondDigit += 3;
        secondDigit++;
        if (secondDigit > 57) secondDigit = 48;
      //Second digit of the cols index (1..26) will be 0-9
      } else if (i == 0 && j == initialColsCoordinateOfFirstDigit) {
        grid[i][j] = (firstDigit == 48) ? ' ' : firstDigit;
        initialColsCoordinateOfFirstDigit += 3;
        if (secondDigit > 56) firstDigit++;
      //Dash seperator '-------------------'
      } else if (i == 1 && j > 1) {
        grid[i][j] = '-';
      //'|' sepeartor between cells
      } else if (i > 1 && j == initialColsCoordinateOfDashSeperator) {
        grid[i][j] = '|';
        initialColsCoordinateOfDashSeperator += 3;
        if (initialColsCoordinateOfDashSeperator > b.getColsCharLength()) initialColsCoordinateOfDashSeperator = 2;
      //The rows index (A..Z)
      } else if (j == 0 && i > 1) {
        grid[i][j] = i + 63;
      //Fill the empty char with ' '
      } else {
        grid[i][j] = ' ';
      }
  return;
}

//Update the tile position if new tile added into the board
void BoardDisplay::placeTile(Grid& grid, Board& b) {
  for (int i = 0; i < b.getRows(); i++) {
    for (int j = 0; j < b.getCols(); j++) {
      Coordinate c = Coordinate(i, j);
      if (b.containAt(c)) {
        grid[j + 2][i * 3 + 3] = b.getTileAt(c).getColour();
        grid[j + 2][i * 3 + 4] = b.getTileAt(c).getShape() + 48;
      }
    }
  }
}

void BoardDisplay::printGrid(Grid grid, Board& b) {
  for (int i = 0; i < b.getRowsCharLength(); i++) {
    for (int j = 0; j < b.getColsCharLength(); j++) {
      std::cout << grid[i][j];
    }
    std::cout << "\n";
  }
  return;
}

void BoardDisplay::deleteGrid(Grid grid, Board& b) {
  if (b.getRowsCharLength() >= 0 && b.getColsCharLength() >= 0) {
    for (int i = 0; i != b.getRowsCharLength(); ++i) {
      delete grid[i];
    }
    delete grid;
  }
  return;
}
