
#include "Tile.h"


Tile::Tile(Colour colour, Shape shape)
{
    this->colour = colour;
    this->shape = shape;
}

//this is for initializing a tile without definite value and set 
//field when meet condition-same ideas with particle
Tile::Tile()
{
    this->colour = ' ';
}

//Implementing a DEEP COPY in CC of Node
Tile::Tile(Tile& other)
{
    this->colour = other.colour;
    this->shape = other.shape;
}

Tile::~Tile()
{

}

Colour Tile::getColour()
{
    return this->colour;
}

Shape Tile::getShape()
{
    return this->shape;
}

void Tile::setColour(Colour colour)
{
    this->colour = colour;
}

void Tile::setShape(Shape shape)
{
    this->shape = shape;
}

std::string Tile::displayTile(Tile& tile)
{
    std::string result = "";
    
    //when there is a tile 
    if(tile.getColour() != ' ')
    {
     result = tile.getColour() + std::to_string(tile.getShape());
    }
    else
    {
     result = tile.getColour() + " ";
    }
    
    return result; 

}

