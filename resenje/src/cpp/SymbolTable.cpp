#include "../hpp/SymbolTable.hpp"


SymbolTableEntry::SymbolTableEntry(){}
SymbolTable::SymbolTable(){
  this->firstEntry = nullptr;
  this->indexCounter = 0;
}
SymbolTableEntry* SymbolTable::declareSymbolLocal(std::string symbol,int isSection){
    bool found = false;
  SymbolTableEntry* currentEntry = this->firstEntry;
  SymbolTableEntry* prev = nullptr;
  SymbolTableEntry* retEntry = nullptr;
  while(currentEntry!=nullptr){
    if(currentEntry->name == symbol){
      currentEntry->bind = 'l';
      found = true;
      retEntry = currentEntry;
      break;
    }
    prev = currentEntry;
    currentEntry = currentEntry->nextEntry;
  }
  if(!found){
    SymbolTableEntry* newEntry = new SymbolTableEntry();
    newEntry->name = symbol;
    newEntry->defined = false;
    newEntry->bind = 'l';
    newEntry->index = this->indexCounter++;
    newEntry->belongsTo = -1;
    if(isSection == 1){
      newEntry->type = "SECT";
    }
    else{
      newEntry->type = "NOTYP";
    }
    newEntry->value = 0;
    newEntry->size = 0;
    //TODO: INIT FLINK
    if(prev){
      prev->nextEntry = newEntry;
    }
    else{
      this->firstEntry = newEntry;
    }
    retEntry = newEntry;
  }
  return retEntry;
}
void SymbolTable::declareSymbolGlobal(std::string symbol, Section* currentSection){
  bool found = false;
  SymbolTableEntry* currentEntry = this->firstEntry;
  SymbolTableEntry* prev = nullptr;
  while(currentEntry!=nullptr){
    if(currentEntry->name == symbol){
      currentEntry->bind = 'g';
      found = true;
      break;
    }
    prev = currentEntry;
    currentEntry = currentEntry->nextEntry;
  }
  if(!found){
    SymbolTableEntry* newEntry = new SymbolTableEntry();
    newEntry->name = symbol;
    newEntry->defined = false;
    newEntry->bind = 'g';
    newEntry->index = this->indexCounter++;
    if(currentSection){
      newEntry->belongsTo = currentSection->myEntry->index;
    }
    else{
      newEntry->belongsTo = -1;
    }
    newEntry->type = "NOTYP";
    newEntry->value = 0;
    newEntry->size = 0;
    //TODO: INIT FLINK
    if(prev){
      prev->nextEntry = newEntry;
    }
    else{
      this->firstEntry = newEntry;
    }
  }
}
SymbolTableEntry* SymbolTable::getFirstEntry(){
    return this->firstEntry;
}
void SymbolTable::printSymbolTable(){
  printf("Num\tValue\tSize\tType\tBind\tNdx\tName\n");
  SymbolTableEntry*curr = this->getFirstEntry();
  while (curr!=nullptr)
  {
    printf("%d\t",curr->index);
    printf("%ld\t",curr->value);
    printf("%d\t",curr->size);
    printf("%s\t", curr->type.c_str());
    printf("%c\t",curr->bind);
    if(curr->belongsTo == -1){
      printf("UND\t");
    }
    else{
      printf("%s\t",this->getSymbolNameOfIndex(curr->belongsTo).c_str());
    }
    printf("%s\t",curr->name.c_str());
    printf("\n");
    curr = curr->nextEntry;
  }
  
}
std::string SymbolTable::getSymbolNameOfIndex(unsigned int idx){
  SymbolTableEntry* curr = this->getFirstEntry();
  while(curr!=nullptr){
    if(curr->index == idx){
      return curr->name;
    }
    curr = curr->nextEntry;
  }
  return "";
}