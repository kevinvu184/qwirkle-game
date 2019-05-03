
#include "Tile.h"

Tile::Tile(Colour c, Shape s){
  this->colour = c;
  this->shape = s;
}

Tile::Tile() {
  shape = 0;
  colour = ' ';
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

  bool result = false;
  if(this->colour == t->getColour() && this->shape == t->getShape()){
    result = true;
  }
  
  return result; 
}

// std::string Tile::toString() {
//   return colour + ((shape == 0) ? " " : std::to_string(shape));
// }

// bool Tile::isExist() {
//   return (shape != 0 || colour != ' ');
// }
