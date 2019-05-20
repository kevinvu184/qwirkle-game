#include "Board.h"

Board::Board() {
	m_numberOfTileInThisTurn = INITIAL_STATE;
	m_orientationOfTileInThisTurn = INITIAL_STATE;
	m_qwirkle = INITIAL_STATE;
}

bool Board::addTileAt(Coordinate &coordinate) {
	bool addSuccess = false;

	//If adding the first tile -> No condition
	if (m_coordinate.size() == 0) {
		m_numberOfTileInThisTurn++;
		m_coordinate.push_back(coordinate);
		addSuccess = true;
	} else {
		coordinate.relocateX(getWestBound());
		coordinate.relocateY(getNorthBound());

		//check if the coordinate is empty and have at least 1 surrounding tile
		if (isAddable(coordinate)) {
			m_numberOfTileInThisTurn++;
			m_coordinate.push_back(coordinate);
			if (m_numberOfTileInThisTurn == TWO_TILES_ADD) {
				m_orientationOfTileInThisTurn = getAddOrientation();
			}
			//check if the place if valid (same colour or shape but not both with 1 of the tile in row or col)
			if (isValidForOneCoordinateCondition()
					&& isValsidForMultiplePlaceCondition()) {
				addSuccess = true;
			} else {
				m_numberOfTileInThisTurn--;
				if (m_numberOfTileInThisTurn == ONE_TILE_ADD) {
					m_numberOfTileInThisTurn = INITIAL_STATE;
				}
				m_coordinate.pop_back();
				addSuccess = false;
			}
		}
	}
	return addSuccess;
}

Tile Board::getTileAt(Coordinate coordinate) {
	Tile t = Tile();
	for (unsigned int i = 0; i < m_coordinate.size(); ++i) {
		if (m_coordinate[i] == coordinate)
			t = m_coordinate[i].getTile();
	}
	return t;
}

int Board::getNorthBound() {
	int length = MIN_NORTH;
	for (Coordinate c : m_coordinate) {
		if (c.getY() <= length) {
			length = c.getY() - 1;
		}
	}
	return length;
}

int Board::getSouthBound() {
	int length = MIN_SOUTH;
	for (Coordinate c : m_coordinate) {
		if (c.getY() >= length) {
			length = c.getY() + 1;
		}
	}
	return length;
}

int Board::getWestBound() {
	int length = MIN_WEST;
	for (Coordinate c : m_coordinate) {
		if (c.getX() <= length) {
			length = c.getX() - 1;
		}
	}
	return length;
}

int Board::getEastBound() {
	int length = MIN_EAST;
	for (Coordinate c : m_coordinate) {
		if (c.getX() >= length) {
			length = c.getX() + 1;
		}
	}
	return length;
}

std::ostream &operator<<(std::ostream &out, Board &b) {
	//Column index
	out << "  ";
	int colIndex = 0;
	for (int i = b.getWestBound(); i < b.getEastBound() + 1; ++i) {
		std::string index = std::to_string(colIndex);
		if (colIndex < 10) {
			out << " " << index << " ";
		} else {
			out << " " << index.substr(0, 1) << index.substr(1, 1);
		}
		colIndex++;
	}

	//Dash seperator ---
	out << "\n" << "  -";
	for (int i = b.getWestBound(); i < b.getEastBound() + 1; ++i) {
		out << "---";
	}

	out << "\n";
	char c = 'A';
	for (int i = b.getNorthBound(); i < b.getSouthBound() + 1; ++i) {
		std::string s = "";
		s.push_back(c);
		out << c << " |";
		for (int j = b.getWestBound(); j < b.getEastBound() + 1; ++j) {
			bool has = false;
			for (Coordinate c : b.m_coordinate) {
				if (c.getX() == j && c.getY() == i) {
					out << c.getTile() << "|";
					has = true;
				}
			}
			if (!has) {
				out << "  |";
			}
		}
		out << "\n";
		c++;
	}

	return out;
}

bool Board::hasTileAt(Coordinate coordinate) {
	bool has = false;
	for (Coordinate c : m_coordinate) {
		if (c == coordinate) {
			has = true;
		}
	}
	return has;
}

bool Board::hasNorth(Coordinate coordinate) {
	coordinate.relocateY(-1);
	return hasTileAt(coordinate);
}

bool Board::hasSouth(Coordinate coordinate) {
	coordinate.relocateY(1);
	return hasTileAt(coordinate);
}

bool Board::hasWest(Coordinate coordinate) {
	coordinate.relocateX(-1);
	return hasTileAt(coordinate);
}

bool Board::hasEast(Coordinate coordinate) {
	coordinate.relocateX(1);
	return hasTileAt(coordinate);
}

bool Board::isAddable(Coordinate coordinate) {
	return !hasTileAt(coordinate)
			&& (hasNorth(coordinate) || hasSouth(coordinate)
					|| hasWest(coordinate) || hasEast(coordinate));
}

int Board::numOfNorthTile(Coordinate coordinate) {
	int num = 0;
	while (hasNorth(coordinate)) {
		coordinate.relocateY(-1);
		num++;
	}
	return num;
}

int Board::numOfSouthTile(Coordinate coordinate) {
	int num = 0;
	while (hasSouth(coordinate)) {
		coordinate.relocateY(1);
		num++;
	}
	return num;
}

int Board::numOfWestTile(Coordinate coordinate) {
	int num = 0;
	while (hasWest(coordinate)) {
		coordinate.relocateX(-1);
		num++;
	}
	return num;
}

int Board::numOfEastTile(Coordinate coordinate) {
	int num = 0;
	while (hasEast(coordinate)) {
		coordinate.relocateX(1);
		num++;
	}
	return num;
}

int Board::numOfColTile(Coordinate coordinate) {
	return numOfNorthTile(coordinate) + numOfSouthTile(coordinate) + 1;
}

int Board::numOfRowTile(Coordinate coordinate) {
	return numOfWestTile(coordinate) + numOfEastTile(coordinate) + 1;
}

int Board::rowPoint(Coordinate coordinate) {
	int rowPoint =
			(hasWest(coordinate) || hasEast(coordinate)) ?
					numOfRowTile(coordinate) : 0;
	if (rowPoint == 6) {
		rowPoint += 6;
		m_qwirkle = true;
	}

	return rowPoint;
}

int Board::colPoint(Coordinate coordinate) {
	int colPoint =
			(hasNorth(coordinate) || hasSouth(coordinate)) ?
					numOfColTile(coordinate) : 0;
	if (colPoint == 6) {
		colPoint += 6;
		m_qwirkle = true;
	}

	return colPoint;
}

int Board::getAddOrientation() {
	int orientation = INVALID_ADD;
	if (m_coordinate.end()[-1].getX() == m_coordinate.end()[-2].getX()) {
		orientation = VERTICAL_ADD;
	} else if (m_coordinate.end()[-1].getY() == m_coordinate.end()[-2].getY()) {
		orientation = HORIZONTAL_ADD;
	}
	return orientation;
}

int Board::pointWhenPlayerPlaceOneTile() {
	Coordinate coordinate = m_coordinate.back();
	int cPoint = colPoint(coordinate);
	int rPoint = rowPoint(coordinate);
	int sum = cPoint + rPoint;
	return (sum == 0) ? 1 : sum;
}

int Board::pointWhenPlayerPlaceHorizontalTiles() {
	Coordinate coordinate = m_coordinate.back();
	std::vector<Coordinate> newTileThisTurn(
			m_coordinate.end() - m_numberOfTileInThisTurn, m_coordinate.end());
	int rPoint = rowPoint(coordinate);
	int cPoint = 0;

	for (Coordinate c : newTileThisTurn) {
		cPoint += colPoint(c);
	}

	return cPoint + rPoint;
}

int Board::pointWhenPlayerPlaceVerticalTiles() {
	Coordinate coordinate = m_coordinate.back();
	std::vector<Coordinate> newTileThisTurn(
			m_coordinate.end() - m_numberOfTileInThisTurn, m_coordinate.end());
	int cPoint = colPoint(coordinate);
	int rPoint = 0;

	for (Coordinate c : newTileThisTurn) {
		rPoint += rowPoint(c);
	}

	return cPoint + rPoint;
}

int Board::totalPoint() {
	int point = 0;
	if (m_numberOfTileInThisTurn == ONE_TILE_ADD) {
		point = pointWhenPlayerPlaceOneTile();
	} else if (m_numberOfTileInThisTurn >= TWO_TILES_ADD) {
		if (m_orientationOfTileInThisTurn == VERTICAL_ADD) {
			point = pointWhenPlayerPlaceVerticalTiles();
		} else if (m_orientationOfTileInThisTurn == HORIZONTAL_ADD) {
			point = pointWhenPlayerPlaceHorizontalTiles();
		}
	}
	m_numberOfTileInThisTurn = INITIAL_STATE;
	m_orientationOfTileInThisTurn = INITIAL_STATE;
	m_qwirkle = INITIAL_STATE;
	return point;
}

bool Board::isQwirkle() {
	return m_qwirkle;
}

std::vector<Tile> Board::colLine() {
	std::vector<Tile> line;
	line.reserve(6);

	Coordinate c1 = m_coordinate.back();
	while (numOfSouthTile(c1) > 0) {
		c1.relocateY(1);
		line.push_back(getTileAt(c1));
	}

	Coordinate c2 = m_coordinate.back();
	while (numOfNorthTile(c2) > 0) {
		c2.relocateY(-1);
		line.push_back(getTileAt(c2));
	}

	line.push_back(m_coordinate.back().getTile());
	return line;
}

std::vector<Tile> Board::rowLine() {
	std::vector<Tile> line;
	line.reserve(6);

	Coordinate c1 = m_coordinate.back();
	while (numOfWestTile(c1) > 0) {
		c1.relocateX(-1);
		line.push_back(getTileAt(c1));
	}

	Coordinate c2 = m_coordinate.back();
	while (numOfEastTile(c2) > 0) {
		c2.relocateX(1);
		line.push_back(getTileAt(c2));
	}

	line.push_back(m_coordinate.back().getTile());
	return line;
}

bool Board::verifyByLine(std::vector<Tile> line) {
	bool sameColour = true;
	bool sameShape = true;
	bool identical = false;

//brute force approach
	for (unsigned int i = 0; i < line.size(); ++i) {
		for (unsigned int j = i + 1; j < line.size(); ++j) {
			if (line[i] == line[j]) {
				identical = true;
			}
			if (!line[i].isSameColour(line[j])) {
				sameColour = false;
			}
			if (!line[i].isSameShape(line[j])) {
				sameShape = false;
			}
		}
	}
	return !identical && (sameShape || sameColour);
}

bool Board::isValidForOneCoordinateCondition() {
	return verifyByLine(rowLine()) && verifyByLine(colLine());
}

bool Board::validateHorizontalAdd() {
	bool isValid = false;
	if (((m_coordinate.end()[-1].getX() + 1 == m_coordinate.end()[-2].getX())
			|| (m_coordinate.end()[-1].getX() - 1
					== m_coordinate.end()[-2].getX()))
			&& (m_coordinate.end()[-1].getY() == m_coordinate.end()[-2].getY())) {
		isValid = true;
	}
	return isValid;
}

bool Board::validateVerticalAdd() {
	bool isValid = false;
	if (((m_coordinate.end()[-1].getY() + 1 == m_coordinate.end()[-2].getY())
			|| (m_coordinate.end()[-1].getY() - 1
					== m_coordinate.end()[-2].getY()))
			&& (m_coordinate.end()[-1].getX() == m_coordinate.end()[-2].getX())) {
		isValid = true;

	}
	return isValid;
}
bool Board::validateSecondTileCondition() {
	bool isValid = false;
	if (validateHorizontalAdd() || validateVerticalAdd()) {
		isValid = true;
	}
	return isValid;
}

bool Board::validateMoreThanTwoTileCondition() {
	bool isValid = false;
	if (m_orientationOfTileInThisTurn == HORIZONTAL_ADD
			&& validateHorizontalAdd()) {
		isValid = true;
	} else if (m_orientationOfTileInThisTurn == VERTICAL_ADD
			&& validateVerticalAdd()) {
		isValid = true;
	}
	return isValid;
}
bool Board::isValsidForMultiplePlaceCondition() {
	bool isValid = false;
	if (m_numberOfTileInThisTurn == TWO_TILES_ADD
			&& validateSecondTileCondition()) {
		isValid = true;
	} else if (m_numberOfTileInThisTurn > TWO_TILES_ADD
			&& validateMoreThanTwoTileCondition()) {
		isValid = true;
	} else if (m_numberOfTileInThisTurn == ONE_TILE_ADD) {
		isValid = true;
	}
	return isValid;
}
