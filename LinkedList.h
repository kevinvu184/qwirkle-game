
#ifndef ASSIGN2_LINKEDLIST_H
#define ASSIGN2_LINKEDLIST_H

#include "Node.h"
#include <string>

class LinkedList {
public:

   LinkedList();
   ~LinkedList();

   int getSize();
   // void addFront(Tile* t);
   void addBack(Tile* t);
   void removeFirst();
   bool contains(Tile* t);
   Tile* get(int index);
   // void removeLast();
   std::string displayList();
   void remove(Tile* tile);

private:
   Node* head;
   int size;
};

#endif // ASSIGN2_LINKEDLIST_H
