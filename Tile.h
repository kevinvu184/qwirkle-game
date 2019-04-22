
#ifndef ASSIGN2_TILE_H
#define ASSIGN2_TILE_H

#include "TileCodes.h"
#include <string> 


// Define a Colour type
typedef char Colour;

// Define a Shape type
typedef int Shape;

class Tile {
public:

   Tile(Colour color, int Shape);

   Tile(Tile& other);

   Tile();

   ~Tile();

   char getColour();

   int getShape();

   void setColour(Colour colour);

   void setShape(Shape shape);

   //this is to display the board 
   std::string displayTile(Tile& tile);
 
   

private:
   Colour colour;
   Shape  shape;
};

#endif // ASSIGN2_TILE_H
