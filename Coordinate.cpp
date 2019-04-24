#include "Coordinate.h"

Coordinate::Coordinate() {

}

Coordinate::Coordinate(int x, int y) {
  setXY(x, y);
}

Coordinate::Coordinate(int x, char y) {
  setXY(x, y - 65);
}

void Coordinate::setXY(int x, int y) {
  m_x = x;
  m_y = y;
}

int Coordinate::getX() {
  return m_x;
}

int Coordinate::getY() {
  return m_y;
}

std::string Coordinate::toString() {
  return static_cast<char>(m_y + 65) + std::to_string(m_x);
}
