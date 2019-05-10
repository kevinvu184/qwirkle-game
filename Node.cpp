
#include "Node.h"

Node::Node(Tile* tile, Node* next)
{
   //deep copy of tile now  
   this->tile =  new Tile(tile->getColour(), tile->getShape());
   this->next = next;
}

Node::~Node()
{
   delete tile; 
}

Node::Node(Node& other)
{
   //this is to implement a DEEP COPY case study with character
   this->tile = new Tile(*(other.tile));

   this->next = other.next;

}
