#include "Board.h"

Board::Board()
{
	m_northBound = NORTH;
	m_southBound = SOUTH;
	m_westBound = WEST;
	m_eastBound = EAST;
	m_coordinate.reserve(12);
}

bool Board::addTileAt(Coordinate &coordinate)
{
	if (m_coordinate.size() == 0)
	{
		m_coordinate.push_back(coordinate);
		return false;
	}
	else
	{
		coordinate.relocateX(westBound());
		coordinate.relocateY(northBound());
		if (isAddable(coordinate))
		{
			m_coordinate.push_back(coordinate);
		} else {
			return false;
		}
		if (!verifyMove())
		{
			removeLastTile();
			return false;
		}
	}
	return true;
}

void Board::removeLastTile()
{
	m_coordinate.pop_back();
	resize();
}

Tile Board::getTileAt(Coordinate coordinate)
{
	Tile t = Tile();
	for (unsigned int i = 0; i < m_coordinate.size(); ++i)
	{
		if (m_coordinate[i] == coordinate)
			t = m_coordinate[i].getTile();
	}
	return t;
}

Tile Board::getLatestTile()
{
	Tile t = m_coordinate[m_coordinate.size() - 1].getTile();
	return t;
}

int Board::northBound()
{
	for (Coordinate c : m_coordinate)
	{
		if (c.getY() <= m_northBound)
		{
			m_northBound = c.getY() - 1;
		}
	}
	return m_northBound;
}

int Board::southBound()
{
	for (Coordinate c : m_coordinate)
	{
		if (c.getY() >= m_southBound)
		{
			m_southBound = c.getY() + 1;
		}
	}
	return m_southBound;
}

int Board::westBound()
{
	for (Coordinate c : m_coordinate)
	{
		if (c.getX() <= m_westBound)
		{
			m_westBound = c.getX() - 1;
		}
	}
	return m_westBound;
}

int Board::eastBound()
{
	for (Coordinate c : m_coordinate)
	{
		if (c.getX() >= m_eastBound)
		{
			m_eastBound = c.getX() + 1;
		}
	}
	return m_eastBound;
}

void Board::resize()
{
	for (Coordinate c : m_coordinate)
	{
		while (m_northBound < c.getY() - 1 && m_northBound < NORTH)
		{
			m_northBound++;
		}
		while (m_southBound > c.getY() + 1 && m_southBound > SOUTH)
		{
			m_southBound--;
		}
		while (m_westBound < c.getX() - 1 && m_westBound < WEST)
		{
			m_westBound++;
		}
		while (m_eastBound > c.getX() + 1 && m_eastBound > EAST)
		{
			m_eastBound--;
		}
	}
}

std::ostream &operator<<(std::ostream &out, Board &b)
{
	//Column index
	out << "  ";
	int colIndex = 0;
	for (int i = b.westBound(); i < b.eastBound() + 1; ++i)
	{
		std::string index = std::to_string(colIndex);
		if (colIndex < 10)
		{
			out << " " << index << " ";
		}
		else
		{
			out << " " << index.substr(0, 1) << index.substr(1, 1);
		}
		colIndex++;
	}

	//Dash seperator ---
	out << "\n"
			<< "  -";
	for (int i = b.westBound(); i < b.eastBound() + 1; ++i)
	{
		out << "---";
	}

	out << "\n";
	char c = 'A';
	for (int i = b.northBound(); i < b.southBound() + 1; ++i)
	{
		std::string s = "";
		s.push_back(c);
		out << c << " |";
		for (int j = b.westBound(); j < b.eastBound() + 1; ++j)
		{
			bool has = false;
			for (Coordinate c : b.m_coordinate)
			{
				if (c.getX() == j && c.getY() == i)
				{
					out << c.getTile() << "|";
					has = true;
				}
			}
			if (!has)
			{
				out << "  |";
			}
		}
		out << "\n";
		c++;
	}

	return out;
}

bool Board::hasTileAt(Coordinate coordinate)
{
	bool has = false;
	for (Coordinate c : m_coordinate)
	{
		if (c == coordinate)
		{
			has = true;
		}
	}
	return has;
}

bool Board::hasNorth(Coordinate coordinate)
{
	coordinate.relocateY(-1);
	return hasTileAt(coordinate);
}

bool Board::hasSouth(Coordinate coordinate)
{
	coordinate.relocateY(1);
	return hasTileAt(coordinate);
}

bool Board::hasWest(Coordinate coordinate)
{
	coordinate.relocateX(-1);
	return hasTileAt(coordinate);
}

bool Board::hasEast(Coordinate coordinate)
{
	coordinate.relocateX(1);
	return hasTileAt(coordinate);
}

bool Board::isAddable(Coordinate coordinate)
{
	return !hasTileAt(coordinate) && (hasNorth(coordinate) || hasSouth(coordinate) || hasWest(coordinate) || hasEast(coordinate));
}

int Board::numOfNorthTile(Coordinate coordinate)
{
	int num = 0;
	while (hasNorth(coordinate))
	{
		coordinate.relocateY(-1);
		num++;
	}
	return num;
}

int Board::numOfSouthTile(Coordinate coordinate)
{
	int num = 0;
	while (hasSouth(coordinate))
	{
		coordinate.relocateY(1);
		num++;
	}
	return num;
}

int Board::numOfWestTile(Coordinate coordinate)
{
	int num = 0;
	while (hasWest(coordinate))
	{
		coordinate.relocateX(-1);
		num++;
	}
	return num;
}

int Board::numOfEastTile(Coordinate coordinate)
{
	int num = 0;
	while (hasEast(coordinate))
	{
		coordinate.relocateX(1);
		num++;
	}
	return num;
}

int Board::numOfColTile(Coordinate coordinate)
{
	return numOfNorthTile(coordinate) + numOfSouthTile(coordinate) + 1;
}

int Board::numOfRowTile(Coordinate coordinate)
{
	return numOfWestTile(coordinate) + numOfEastTile(coordinate) + 1;
}

int Board::totalPoint(Coordinate coordinate)
{
	int colPoint =
			(hasNorth(coordinate) || hasSouth(coordinate)) ? numOfColTile(coordinate) : 0;
	if (colPoint == 6)
		colPoint += 6;
	int rowPoint =
			(hasWest(coordinate) || hasEast(coordinate)) ? numOfRowTile(coordinate) : 0;
	if (rowPoint == 6)
		rowPoint += 6;
	int sum = colPoint + rowPoint;
	return (sum == 0) ? 1 : sum;
}

std::vector<Tile> Board::colLine()
{
	std::vector<Tile> line;
	line.reserve(6);

	Coordinate c1 = m_coordinate.back();
	while (numOfSouthTile(c1) > 0)
	{
		c1.relocateY(1);
		line.push_back(getTileAt(c1));
	}

	Coordinate c2 = m_coordinate.back();
	while (numOfNorthTile(c2) > 0)
	{
		c2.relocateY(-1);
		line.push_back(getTileAt(c2));
	}

	line.push_back(getLatestTile());
	return line;
}

std::vector<Tile> Board::rowLine()
{
	std::vector<Tile> line;
	line.reserve(6);

	Coordinate c1 = m_coordinate.back();
	while (numOfWestTile(c1) > 0)
	{
		c1.relocateX(-1);
		line.push_back(getTileAt(c1));
	}

	Coordinate c2 = m_coordinate.back();
	while (numOfEastTile(c2) > 0)
	{
		c2.relocateX(1);
		line.push_back(getTileAt(c2));
	}

	line.push_back(getLatestTile());
	return line;
}

bool Board::verify(std::vector<Tile> line)
{
	bool sameColour = true;
	bool sameShape = true;
	bool identical = false;

	//brute force approach
	for (unsigned int i = 0; i < line.size(); ++i)
	{
		for (unsigned int j = i + 1; j < line.size(); ++j)
		{
			if (line[i] == line[j])
			{
				identical = true;
			}
			if (!line[i].isSameColour(line[j]))
			{
				sameColour = false;
			}
			if (!line[i].isSameShape(line[j]))
			{
				sameShape = false;
			}
		}
	}
	return !identical && (sameShape || sameColour);
}

bool Board::verifyMove()
{
	return verify(rowLine()) && verify(colLine());
}
