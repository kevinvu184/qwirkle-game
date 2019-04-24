
#ifndef ASSIGN2_COORDINATE_H
#define ASSIGN2_COORDINATE_H

#include <string>

class Coordinate {
  private:
    int m_x;
    int m_y;

  public:
    Coordinate();
    Coordinate(int x, int y);
    Coordinate(int x, char y);

    void setXY(int x, int y);

    int getX();
    int getY();

    std::string toString();
};

#endif //ASSIGN2_COORDINATE_H
