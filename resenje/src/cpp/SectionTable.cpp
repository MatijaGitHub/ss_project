#include "../hpp/SectionTable.hpp"


SectionTable::SectionTable(){
  this->nextEntry = nullptr;
  this->section = nullptr;
  this->size = 0;
}
Section* SectionTable::getSection(){
  return this->section;
}
SectionTable* SectionTable::getNextEntry(){
  return this->nextEntry;
}
void SectionTable::setSection(Section* sec){
  this->section = sec;
}
void SectionTable::setNextEntry(SectionTable* nxt){
  this->nextEntry = nxt;
}

void SectionTable::printSectionTable(){
  SectionTable* currentTable = this;
  Section* current = currentTable->section;
  while (current!=nullptr)
  {
    if(current->locationCounter > 0){
      printf("#%s\n",current->sectionName.c_str());
      current->readContent();
    }
    currentTable = currentTable->nextEntry;
    if(currentTable == nullptr) break;
    current = currentTable->section;
  }
  
}

void SectionTable::addSectionToTail(Section* sec){
  SectionTable* curr = this;
  if(curr->section == nullptr){
    curr->section = sec;
    this->size++;
    return;
  }
  SectionTable* newEntry = new SectionTable();
  newEntry->section = sec;
  while (curr->nextEntry!=nullptr)
  {
    curr = curr->nextEntry;
  }
  
  curr->nextEntry = newEntry;
  size++;
  
}
void SectionTable::printRelocationTablesForAllSections(SymbolTable* symTab){
  SectionTable* curr = this;
  while (curr!=nullptr)
  {
    curr->section->printRelocationTable(symTab);
    printf("\n");
    curr = curr->nextEntry;
  }
}


int SectionTable::getTableSize(){
  return this->size;
}

int SectionTable::getNumberOfRelocations(){
  int num = 0;
  SectionTable* curr = this;
  while(curr!=nullptr){
    num+=curr->section->myRelocationTable->getRelocationTableSize();
    curr = curr->nextEntry;
  }
  return num;
}