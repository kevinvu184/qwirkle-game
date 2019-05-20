#ifndef ASSIGN2_NODE_H
#define ASSIGN2_NODE_H

#include "Tile.h"

class Node {
  public:

    Node(Tile* tile, Node* next);
    Node(Node& other);
    ~Node();

    //declared as public but is this being public good or bad
    Tile* tile;
    Node* next;
};

#endif // ASSIGN2_NODE_H
