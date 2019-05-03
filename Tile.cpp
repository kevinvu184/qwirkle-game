
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

//Khoa's works
Tile::Tile(const Tile &t) {
	m_colour = t.m_colour;
	m_shape = t.m_shape;
}

bool Tile::isSameColour(const Tile &t) {
	return m_colour == t.m_colour;
}

bool Tile::isSameShape(const Tile &t) {
	return m_shape == t.m_shape;
}

std::ostream &operator<<(std::ostream &out, const Tile &t) {
	out << t.m_colour << std::to_string(t.m_shape);
	return out;
}

Tile &Tile::operator=(const Tile &t) {
	m_colour = t.m_colour;
	m_shape = t.m_shape;
	return *this;
}

bool operator==(const Tile &t1, const Tile &t2) {
	return t1.m_colour == t2.m_colour && t1.m_shape == t2.m_shape;
}
