#ifndef ASSIGN2_BOARD_H
#define ASSIGN2_BOARD_H

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

#include "Coordinate.h"

#define MIN_NORTH -2
#define MIN_SOUTH 2
#define MIN_WEST -2
#define MIN_EAST 2

#define INITIAL_STATE 0
#define ONE_TILE_ADD 1
#define TWO_TILES_ADD 2
#define HORIZONTAL_ADD 3
#define VERTICAL_ADD 4
#define INVALID_ADD 5

class Board {
  private:
    bool m_qwirkle;
    int m_numberOfTileInThisTurn;
    int m_orientationOfTileInThisTurn;

    std::vector<Coordinate> m_coordinate;

  public:
    Board();
    bool addTileAt(Coordinate &coordinate);

    Tile getTileAt(Coordinate coordinate);

    int getNorthBound();
    int getSouthBound();
    int getWestBound();
    int getEastBound();

    friend std::ostream &operator<<(std::ostream &out, Board &b);

    bool hasTileAt(Coordinate coordinate);
    bool hasNorth(Coordinate coordinate);
    bool hasSouth(Coordinate coordinate);
    bool hasWest(Coordinate coordinate);
    bool hasEast(Coordinate coordinate);

    bool isAddable(Coordinate coordinate);

    int numOfNorthTile(Coordinate coordinate);
    int numOfSouthTile(Coordinate coordinate);
    int numOfWestTile(Coordinate coordinate);
    int numOfEastTile(Coordinate coordinate);

    int numOfRowTile(Coordinate coordinate);
    int numOfColTile(Coordinate coordinate);

    int getAddOrientation();

    int colPoint(Coordinate coordinate);
    int rowPoint(Coordinate coordinate);

    int pointWhenPlayerPlaceOneTile();
    int pointWhenPlayerPlaceHorizontalTiles();
    int pointWhenPlayerPlaceVerticalTiles();

    int totalPoint();
    void resetValidation();
    bool isQwirkle();

    std::vector<Tile> colLine();
    std::vector<Tile> rowLine();

    bool verifyByLine(std::vector<Tile> line);
    bool isValidForOneCoordinateCondition();

    bool validateSecondTileCondition();
    bool validateMoreThanTwoTileCondition();
    bool validateHorizontalAdd();
    bool validateVerticalAdd();
    bool isValsidForMultiplePlaceCondition();
};

#endif // ASSIGN2_BOARD_H
