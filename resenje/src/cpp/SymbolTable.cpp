#include "../hpp/SymbolTable.hpp"


SymbolTableEntry::SymbolTableEntry(){
  this->nextEntry = nullptr;
}
SymbolTable::SymbolTable(){
  this->firstEntry = nullptr;
  this->indexCounter = 0;
  this->size = 0;
}
SymbolTableEntry* SymbolTable::defineSymbolLocal(std::string symbol, Section* currentSection){
bool found = false;
  SymbolTableEntry* currentEntry = this->firstEntry;
  SymbolTableEntry* prev = nullptr;
  SymbolTableEntry* retEntry = nullptr;
  while(currentEntry!=nullptr){
    if(currentEntry->name == symbol){
      found = true;
      retEntry = currentEntry;
      currentEntry->belongsTo = currentSection->myEntry->index;
      currentEntry->defined = true;
      currentEntry->value = currentSection->locationCounter;
      break;
      
    }
    prev = currentEntry;
    currentEntry = currentEntry->nextEntry;
    
  }
  if(!found){
    SymbolTableEntry* newEntry = new SymbolTableEntry();
    newEntry->name = symbol;
    newEntry->defined = true;
    newEntry->bind = 'l';
    newEntry->index = this->indexCounter++;
    newEntry->value = currentSection->locationCounter;
    newEntry->belongsTo = currentSection->myEntry->index;
    newEntry->type = "NOTYP";
    newEntry->size = 0;
    if(prev){
      prev->nextEntry = newEntry;
    }
    else{
      this->firstEntry = newEntry;
    }
    size++;
    retEntry = newEntry;
  }
  return retEntry;
}
SymbolTableEntry* SymbolTable::declareSection(std::string symbol,Section* currentSection){
  SymbolTableEntry* currentEntry = this->firstEntry;
  SymbolTableEntry* prev = nullptr;
  SymbolTableEntry* retEntry = nullptr;
  while(currentEntry!=nullptr){
    prev = currentEntry;
    currentEntry = currentEntry->nextEntry;
  }
  SymbolTableEntry* newEntry = new SymbolTableEntry();
  newEntry->name = symbol;
  newEntry->defined = false;
  newEntry->bind = 'l';
  newEntry->index = this->indexCounter++;
  newEntry->value = 0;
  newEntry->belongsTo = newEntry->index;
  newEntry->type = "SECT";
  newEntry->size = 0;
  // newEntry->flink = new ForwardReferenceTableEntry(currentSection->locationCounter);
  if(prev){
    prev->nextEntry = newEntry;
  }
  else{
    this->firstEntry = newEntry;
  }
  size++;
  retEntry = newEntry;
  return retEntry;
}
void SymbolTable::declareSymbolGlobal(std::string symbol,int isExtern ,Section* currentSection){
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
    newEntry->belongsTo = -1;
    newEntry->type = "NOTYP";
    newEntry->value = 0;
    newEntry->size = 0;
    newEntry->flink = nullptr;
    if(prev){
      prev->nextEntry = newEntry;
    }
    else{
      this->firstEntry = newEntry;
    }
    size++;
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
  printf("\n");
}
std::string SymbolTable::getSymbolNameOfIndex(unsigned int idx){
  SymbolTableEntry* curr = this->getFirstEntry();
  while(curr!=nullptr){
    if(curr->index == idx){
      return curr->name;
    }
    curr = curr->nextEntry;
  }
  return "UND";
}

int SymbolTable::getValueBySymbolName(std::string name){
  SymbolTableEntry* entry = this->firstEntry;
  while (entry!=nullptr)
  {
    if(entry->name == name){
      return entry->value;
    }
    entry = entry->nextEntry;
  }
  return -1;
  
}
SymbolTableEntry* SymbolTable::getEntryBySymbolName(std::string name){
  SymbolTableEntry* entry = this->firstEntry;
  while (entry!=nullptr)
  {
    if(entry->name == name){
      return entry;
    }
    entry = entry->nextEntry;
  }
  return nullptr;
  
}

SymbolTableEntry* SymbolTable::declareSymbolLocal(std::string symbol, Section* currentSection,bool isIns,bool isAbsAdr){
  bool found = false;
  SymbolTableEntry* currentEntry = this->firstEntry;
  SymbolTableEntry* prev = nullptr;
  SymbolTableEntry* retEntry = nullptr;
  while(currentEntry!=nullptr){
    if(currentEntry->name == symbol){
      found = true;
      retEntry = currentEntry;
      if(!currentEntry->defined || currentEntry->belongsTo!=currentSection->myEntry->index || isAbsAdr){
        int toPatch = currentSection->locationCounter;
        if(isIns)toPatch+=3;
        if(currentEntry->flink == nullptr) currentEntry->flink = new ForwardReferenceTableEntry(toPatch,currentSection,isAbsAdr,isIns);
        else currentEntry->flink->putForwardReferenceEntry(toPatch,currentSection,isAbsAdr,isIns);
      }
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
    newEntry->type = "NOTYP";
    newEntry->value = 0;
    newEntry->size = 0;
    int toPatch = currentSection->locationCounter;
    if(isIns)toPatch+=3;
    newEntry->flink = new ForwardReferenceTableEntry(toPatch,currentSection,isAbsAdr,isIns);
    if(prev){
      prev->nextEntry = newEntry;
    }
    else{
      this->firstEntry = newEntry;
    }
    size++;
    retEntry = newEntry;
  }
  return retEntry;
}

int SymbolTable::getTableSize(){
  return this->size;
}

void SymbolTable::addEntry(SymbolTableEntry* entry){
  SymbolTableEntry* entryFirst = this->getFirstEntry();
  if(entryFirst == nullptr){
    this->firstEntry = entry;
    return;
  }
  while(entryFirst->nextEntry != nullptr){
    entryFirst = entryFirst->nextEntry;
  }
  entryFirst->nextEntry = entry;
}