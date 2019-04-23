
#include "LinkedList.h"

#include <iostream>

LinkedList::LinkedList() {
   head = nullptr;
   size = 0;
}

LinkedList::~LinkedList() {
  Node* n = head;
  Node* temp = nullptr;
  while (n != nullptr){
    temp = n->next;
    delete n;
    n = temp;
  }
  size = 0;
}

void LinkedList::addBack(Tile*t){
  Node* n = new Node(t,nullptr);
  if(head == nullptr){
    head = n;
  } else {
    Node *tail = head;
    while (tail->next != nullptr){
      tail = tail->next;
    }
    tail->next = n;
  }
  size++;
}

Tile* LinkedList::get(int index){
  Node *indexPtr = head;
  for(int i = 0; i <= index; i++){
    indexPtr = indexPtr->next;
  }
  return indexPtr->tile;
}

bool LinkedList::contains(Tile* t){
  bool found = false;
  Node *node = head;

  while(node != nullptr && found == false){
    if(node->tile->compareTile(t)){
      found = true;
    }
    node = node->next;
  }
  return found;
}

void LinkedList::removeFirst(){
  if(head == nullptr){
    std::cout << "Empty List" << std::endl;
  } else {
    Node* n = head;
    head = head->next;
    delete n;
  }
  size--;
}

std::string LinkedList::displayList() {
   std::string result = "";
   Node* current = head;

   while(current != nullptr) {
      if(current->next != nullptr) {
         result = result + current->tile->getColour() + std::to_string(current->tile->getShape()) +",";
      }
      else {
         result = result + current->tile->getColour() + std::to_string(current->tile->getShape());
      }
   }

   return result;
}

void LinkedList::remove(Tile* tile) {
   if(head != nullptr) {
      Node* toDelete = head;
      while(toDelete->tile->getColour() != tile->getColour() && toDelete->tile->getShape() != tile->getShape() && toDelete != nullptr)
      {
         toDelete = toDelete->next;
      }

      delete toDelete;
      size--;
   }
}

int LinkedList::getSize(){
  return size;
}
