
#ifndef ASSIGN2_TILE_H
#define ASSIGN2_TILE_H

// Define a Colour type
typedef char Colour;

// Define a Shape type
typedef int Shape;

class Tile {
public:
   Colour colour;
   Shape  shape;

   Tile(Colour c, Shape s);

// Getters
   Colour getColour();
   Shape getShape();

// Setters
   void setColour(Colour c);
   void setShape(Shape s);

// compare 2 tiles
   bool compareTile(Tile* t);
};

#endif // ASSIGN2_TILE_H
