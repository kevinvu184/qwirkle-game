#include "Tile.h"

Tile::Tile(Colour c, Shape s)
{
  this->colour = c;
  this->shape = s;
}

Tile::Tile()
{
  shape = 0;
  colour = ' ';
}

Shape Tile::getShape()
{
  return shape;
}

Colour Tile::getColour()
{
  return colour;
}

void Tile::setShape(Shape s)
{
  shape = s;
}

void Tile::setColour(Colour c)
{
  colour = c;
}

bool Tile::compareTile(Tile *t)
{

  bool result = false;
  if (this->colour == t->getColour() && this->shape == t->getShape())
  {
    result = true;
  }

  return result;
}

//Khoa's works
Tile::Tile(const Tile &t)
{
  colour = t.colour;
  shape = t.shape;
}

bool Tile::isSameColour(const Tile &t)
{
  return colour == t.colour;
}

bool Tile::isSameShape(const Tile &t)
{
  return shape == t.shape;
}

std::ostream &operator<<(std::ostream &out, const Tile &t)
{
  out << t.colour << std::to_string(t.shape);
  return out;
}

Tile &Tile::operator=(const Tile &t)
{
  colour = t.colour;
  shape = t.shape;
  return *this;
}

bool operator==(const Tile &t1, const Tile &t2)
{
  return t1.colour == t2.colour && t1.shape == t2.shape;
}
