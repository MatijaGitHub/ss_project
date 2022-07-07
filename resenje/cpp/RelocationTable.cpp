#include "../hpp/RelocationTable.hpp"


RelocationTable::RelocationTable(){
  this->firstEntry = nullptr;
  this->size = 0;
}
RelocationTableEntry* RelocationTable::getFirstEntry(){
  return this->firstEntry;
}
void RelocationTable::addEntry(RelocationTableEntry* newEntry){
  if(this->firstEntry == nullptr){
    this->firstEntry = newEntry;
  }
  else{
    RelocationTableEntry* tail = this->firstEntry;
    while(tail->nextEntry!=nullptr){
      tail = tail->nextEntry;
    }
    tail->nextEntry = newEntry;
  }
  size++;
}
RelocationTableEntry* RelocationTable::getEntryByOffset(long offset){
  RelocationTableEntry* found = this->firstEntry;
  while (found!=nullptr)
  {
   if(found->offset == offset){
    return found;
   }
   found = found->nextEntry;
  }
  return nullptr;
}
int RelocationTable::getRelocationTableSize(){
  return this->size;
}