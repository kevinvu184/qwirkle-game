
#include "LinkedList.h"

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
   Node* current = head;
   Node* copyNode = nullptr;
   while(current != nullptr)
   {
      copyNode = current->next;
      delete current;
      current = copyNode;
   }
   size = 0;
}

bool LinkedList::contains(Tile* tile)
{
   bool found = false;
   Node* current = head;

   while(current != nullptr && found == false)
   {
      if(current->tile->getColour() == tile->getColour() && current->tile->getShape() == tile->getShape())
      {
         found = true;
      }
      current = current->next;
   }

   return found;

}


void LinkedList::remove(Tile* tile)
{
   if(head != nullptr)
   {
      Node* toDelete = head;
      while((toDelete->tile->getColour() != tile->getColour() || toDelete->tile->getShape() != tile->getShape()) && toDelete != nullptr)
      {
         toDelete = toDelete->next;
      }

      delete toDelete;
      size--;
   }

}

int LinkedList::tileExist(Tile* tile)
{
   int count = 0;

   if(head != nullptr)
   {
      Node* current = head;

      while(current != nullptr)
      {
       if(current->tile->getColour() == tile->getColour() && current->tile->getShape() == tile->getShape())
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

   while(current != nullptr)
   {
      if(current->next != nullptr)
      {
         result = result + current->tile->getColour() + std::to_string(current->tile->getShape()) +",";
      }
      else
      {
         result = result + current->tile->getColour() + std::to_string(current->tile->getShape());
      }
   }

   return result;
}
