#ifndef ASSIGN2_TILE_H
#define ASSIGN2_TILE_H

#include "TileCodes.h"
#include <iostream>
#include <string>

// Define a Colour type
typedef char Colour;

// Define a Shape type
typedef int Shape;

class Tile {
  public:
    // Constructors
    Tile(Colour c, Shape s);
    Tile();

    // Getters
    Colour getColour();
    Shape getShape();

    // Setters
    void setColour(Colour c);
    void setShape(Shape s);

    // compare 2 tiles
    bool compareTile(Tile *t);

    // Khoa's works:
    Tile(const Tile &t);
    bool isSameColour(const Tile &t);
    bool isSameShape(const Tile &t);
    friend std::ostream &operator<<(std::ostream &out, const Tile &t);
    Tile &operator=(const Tile &t);
    friend bool operator==(const Tile &t1, const Tile &t2);

  private:
    Colour colour;
    Shape shape;
};

#endif // ASSIGN2_TILE_H
