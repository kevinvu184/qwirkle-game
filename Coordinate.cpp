#include "Coordinate.h"

#include <string>

Coordinate::Coordinate(char y, int x)
{
	m_x = x;
	m_y = y - 65;
}

Coordinate::Coordinate(char y, int x, Tile t)
{
	m_x = x;
	m_y = y - 65;
	m_tile = t;
}

Coordinate::Coordinate(const Coordinate &c)
{
	m_y = c.m_y;
	m_x = c.m_x;
	m_tile = c.m_tile;
}

int Coordinate::getX()
{
	return m_x;
}

int Coordinate::getY()
{
	return m_y;
}

Tile Coordinate::getTile()
{
	return m_tile;
}

std::ostream &operator<<(std::ostream &out, const Coordinate &c)
{
	out << (char)(c.m_y + 65) << c.m_x;
	return out;
}

Coordinate &Coordinate::operator=(const Coordinate &c)
{
	m_y = c.m_y;
	m_x = c.m_x;
	m_tile = c.m_tile;
	return *this;
}

bool operator==(const Coordinate &c1, const Coordinate &c2)
{
	return c1.m_x == c2.m_x && c1.m_y == c2.m_y;
}

void Coordinate::relocateX(int x)
{
	m_x += x;
}

void Coordinate::relocateY(int y)
{
	m_y += y;
}
