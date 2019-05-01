
#ifndef ASSIGN2_LINKEDLIST_H
#define ASSIGN2_LINKEDLIST_H

#include "Node.h"
#include <string>


class LinkedList {
public:

   LinkedList();
   ~LinkedList();

   //When removing a tile from tile bag
   void deleteFront();

   //when adding tile at any linkedlist
   void addBack(Tile* tile);

   //player hand add the front tile of tile bag 
   //should get front tile from tile bag
   Tile* getFront();

   //maybe for game state checking 
   //i.e: endgame state 
   int getSize();

   //after game ends we need to erase the remaining tile in one of
   //player's hand
   void clear();

   //when player request for placing or replacing 
   //check first if exist 
   bool contains(Tile* tileToBeCompared);

   //when placing or replacing tile on player's hand
   //that selected tile being removed
   void remove(Tile* tileToBeRemoved);

   // void addFront(int data);
   // int get(int i);

   //function to count how many time a specific tile exist
   int tileExist(Tile* tileToBeCompared);

   //display list - to construct a toString() representation of the 
   //linkedlist when displaying tile in player's hand
   std::string displayList();

   //when player request to place/replace tile we have to get 
   //that specific tile from the list for validation 
   //this can be done using contain() if yes then using input tile
   //for validation
   // Tile* getSpecificTile(Tile* tile);


   /*
   LinkedListDesign

   Flow between two LinkedLists (supposing there is no mistake from player in requesting tile):
   player request tile -> check contain ? (bool contains)
   then placing that tile on board and remove that tile from player's hand(void remove)
   player draw = add 1 tile (addBack) from tileBag (getFront when creating a node to add)
   delete that tile drawn from tileBag(deleteFront)
   
   constantly check game state(getSize) 

   at end game state -> there will be one player still keeping tiles -> clear those tile (void clear)

   */




   /*
                                  Shuffle Algorithm 
   WHILE LOOP 72 times for 72 tiles   
      CREATE a tile with colour and shape randomly selected from collection of colour and shape respectively
      (using random generator to generate index in order to randomly select from the two collections)
      WHILE tile created appears two times in the list
          CREATE another randome tile
      END WHILE
      ADD the tile to the list
   END WHILE

   */



   Node* head;
   Node* tail;
   int size;
};

#endif // ASSIGN2_LINKEDLIST_H
