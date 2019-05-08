#ifndef ASSIGN2_BOARD_H
#define ASSIGN2_BOARD_H

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

#include "Coordinate.h"

#define NORTH 0
#define SOUTH 25
#define WEST 0
#define EAST 25

class Board
{
private:
	int m_northBound;
	int m_southBound;
	int m_westBound;
	int m_eastBound;

	std::vector<Coordinate> m_coordinate;

public:
	Board();
	bool addTileAt(Coordinate &coordinate);
	void removeLastTile();

	Tile getTileAt(Coordinate coordinate);
	Tile getLatestTile();

	int northBound();
	int southBound();
	int westBound();
	int eastBound();
	void resize();

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

	int totalPoint(Coordinate coordinate);

	std::vector<Tile> colLine();
	std::vector<Tile> rowLine();

	bool verify(std::vector<Tile> line);
	bool verifyMove();
};

#endif // ASSIGN2_BOARD_H
