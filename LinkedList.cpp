
#include "LinkedList.h"

#include<iostream>

LinkedList::LinkedList() 
{
   head = nullptr;
   tail = nullptr;
   size = 0;
}

LinkedList::~LinkedList() 
{
   clear();
}

void LinkedList::deleteFront()
{
   if(head != nullptr)
   {
      Node* toDelete = head;
      head = toDelete->next;
      delete toDelete;
      size--;
   }
}

void LinkedList::addBack(Tile* tile)
{
      Node* node = new Node(tile, nullptr);
      if(tail != nullptr)
      {
         tail->next = node;
         tail = node;
         size++;
      }
      else
      {
         head = node;
         tail = node;
         size++;
      }
}

Tile* LinkedList::getFront()
{
   return head->tile;
}

int LinkedList::getSize()
{
   return size;
}

void LinkedList::clear()
{
   Node* copyNode = nullptr;
   Node* current = head;

   while(current != nullptr)
   {
      copyNode = current->next;
      delete current;
      current = copyNode;
   }  
   size = 0;
}

bool LinkedList::contains(Tile* tileToBeCompared)
{
   bool found = false;
   Node* current = head;

   while(current != nullptr && found == false)
   {
      if(current->tile->compareTile(tileToBeCompared))
      {
         found = true;
      }
      current = current->next;
   }

   return found;
   
}


void LinkedList::remove(Tile* tileToBeRemoved)
{
   if(head != nullptr)
   {
      Node* toDelete = head;
      while((toDelete->tile->compareTile(tileToBeRemoved) == false) && toDelete != nullptr)
      {
         toDelete = toDelete->next;
      }

      if(toDelete != nullptr)
      {
         delete toDelete;
         size--;
      }
   }

}

int LinkedList::tileExist(Tile* tileToBeCompared)
{
   int count = 0;

   if(head != nullptr)
   {
      Node* current = head;
      
      while(current != nullptr)
      {
       if(current->tile->compareTile(tileToBeCompared))
       {
          count++;
       }

       current = current->next;
      }
   }

   return count;

}

std::string LinkedList::displayList()
{
   std::string result = "";
   Node* current = head;
   // std::cout<<"Debug"<<std::endl;
   while(current != nullptr)
   {
      //in the middle of the list
      if(current->next != nullptr)
      {
         result = result + current->tile->getColour() + std::to_string(current->tile->getShape()) +",";
         
      }
      //at the last element of the list does not need ','
      else
      {
         result = result + current->tile->getColour() + std::to_string(current->tile->getShape());
      }
      current = current->next;      
   }

   return result; 
}
