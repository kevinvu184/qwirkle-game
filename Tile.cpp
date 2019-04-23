
#include "Tile.h"

Tile::Tile(Colour c, Shape s){
  this->colour = c;
  this->shape = s;
}

Shape Tile::getShape(){
  return shape;
}

Colour Tile::getColour(){
  return colour;
}

void Tile::setShape(Shape s){
  shape = s;
}

void Tile::setColour(Colour c){
  colour = c;
}

bool Tile::compareTile(Tile* t){
  if(this->colour == t->getColour() && this->shape == t->getShape()){
    return true;
  } else {
    return false;
  }
}
