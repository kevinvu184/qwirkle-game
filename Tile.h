
#ifndef ASSIGN2_TILE_H
#define ASSIGN2_TILE_H

#include <string>

// Define a Colour type
typedef char Colour;

// Define a Shape type
typedef int Shape;

class Tile {
public:
   Colour colour;
   Shape  shape;

// Construcotrs
   Tile(Colour c, Shape s);
   Tile();

// Getters
   Colour getColour();
   Shape getShape();

// Setters
   void setColour(Colour c);
   void setShape(Shape s);

// compare 2 tiles
   bool compareTile(Tile* t);

// toString and isExist
   std::string toString();
   bool isExist();

};

#endif // ASSIGN2_TILE_H
