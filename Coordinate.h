#include <iostream>
#include <vector>

#include "Tile.h"

class Coordinate {
private:
	int m_x;
	int m_y;

	Tile *m_tile;

public:
	Coordinate(char y, int x);
	Coordinate(char y, int x, Tile& t);
	Coordinate(const Coordinate &c);

	int getX();
	int getY();
	Tile* getTile();

	friend std::ostream &operator<<(std::ostream &out, const Coordinate &c);
	Coordinate &operator=(const Coordinate &c);
	friend bool operator==(const Coordinate &c1, const Coordinate &c2);

	void relocateX(int x);
	void relocateY(int y);
	void relocateCentral();
};
