#include "../hpp/SymbolTable.hpp"


SymbolTableEntry::SymbolTableEntry(){}
SymbolTable::SymbolTable(){
  this->firstEntry = nullptr;
  this->indexCounter = 0;
}
void SymbolTable::declareSymbolGlobal(std::string symbol){
  bool found = false;
  SymbolTableEntry* currentEntry = this->firstEntry;
  SymbolTableEntry* prev = nullptr;
  while(currentEntry!=nullptr){
    if(currentEntry->name == symbol){
      currentEntry->bind = 'g';
      found = true;
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
    newEntry->belongsTo = -1;
    newEntry->type = "NOTYP";
    newEntry->value = 0;
    //TODO: INIT FLINK
    if(prev){
      prev->nextEntry = newEntry;
    }
    else{
      this->firstEntry = newEntry;
    }
  }
}