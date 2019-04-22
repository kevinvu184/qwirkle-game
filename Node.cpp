
#include "Node.h"

Node::Node(Tile* tile, Node* next)
{
   this->tile = tile;
   this->next = next;
}

Node::Node(Node& other)
{
   //this is to implement a DEEP COPY case study with character
   this->tile = new Tile(*(other.tile));

   this->next = other.next;

}
