
#include "LinkedList.h"
#include "Player.h"

#include <iostream>
#include <array>
#include<random>

#define EXIT_SUCCESS        0
#define MAXIMUM_TILES_BAG   72
#define MAXIMUM_PLAYER_HAND 6
int randomNumberGenerator();

void setUpTilesInitially(Player* player, LinkedList* list);

void shuffleAndCreateTileBag(LinkedList* list);

int main(void) {
   LinkedList* list = new LinkedList();

   shuffleAndCreateTileBag(list);

   //should players be pointer or reference ? 
   //ask and construct players
   Player* playerA = new Player("Ted");
   Player* playerB = new Player("Kevin");

   setUpTilesInitially(playerA, list);
   setUpTilesInitially(playerB, list);



   delete list;

   std::cout << "TODO: Implement Qwirkle!" << std::endl;

   return EXIT_SUCCESS;
}

//generate a random number between 0 - 5 
//equally distribution
int randomNumberGenerator(void)
{
   std::random_device rd;
   std::mt19937 eng(rd());
   std::uniform_int_distribution<> distr(0,5);

   return distr(eng);
}

void shuffleAndCreateTileBag(LinkedList* list)
{

   std::array colours = {RED, ORANGE, GREEN, BLUE, PURPLE};
   std::array shapes  = {CIRCLE, STAR_4, DIAMOND, SQUARE, STAR_6, CLOVER};

   //super inefficient as tileExist loop through LinkedList every time 
   //check using tileExist
   //better approach would be to shuffle 
   for(int count = 0; count < MAXIMUM_TILES_BAG; count++)
   {
     Tile* tileToBeAdded = new Tile(colours[randomNumberGenerator()], shapes[randomNumberGenerator()]);
     
     while(list->tileExist(tileToBeAdded) == 2)
     {
        delete tileToBeAdded;
        Tile* tileToBeAdded = new Tile(colours[randomNumberGenerator()], shapes[randomNumberGenerator()]);
     }

     list->addBack(tileToBeAdded);
     delete tileToBeAdded;
   }

/*
                                             Proposed solution for the board 

  Tile** board = new board(26);
  for(int i = 0; i < 26; i++)
  {
     board[i] = new Tile();
  } 

  now suppose player wants to place G5 at C4
  
  using ASCII with 'A' = 65 
  board['C' - 65][4].setColour(G);
  board['C' - 65][4].setShape(5);


  Then call the below code to display the board
   
  std::cout<<" |0 |1 |2 |3 |4 |5 |6 |7 |8 |9 |10 |11 |12 |13 |14 |15 |16 |17 |18 |19 | 20 |21 |22 |23 |24 |25 \n";
  std::cout<<" -----------------------------------------------------------------------------------------------"
  for(int i = 0; i < 26; i++)
  {
    char rows = 'A' + i;

    std::string result = "";
    result = rows + " |";
    for(int j = 0; j < 26; i++)
    {
      result = result + displayTile(board[i][j]) + "|"; 
    }
    std::cout<<"\n";

  }


*/

}


void setUpTilesInitially(Player* player, LinkedList* list)
{
  for(int i = 0; i < MAXIMUM_PLAYER_HAND; ++i)
  {
     player->getCurrentTilesInPlayerHand()->addBack(list->getFront());
     list->deleteFront();
  }

}
