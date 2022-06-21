#include "../hpp/SectionTable.hpp"


SectionTable::SectionTable(){
  this->nextEntry = nullptr;
  this->section = nullptr;
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
    printf("#%s\n",current->sectionName.c_str());
    current->readContent();
    currentTable = currentTable->nextEntry;
    if(currentTable == nullptr) break;
    current = currentTable->section;
  }
  
}

void SectionTable::addSectionToTail(Section* sec){
  SectionTable* curr = this;
  if(curr->section == nullptr){
    curr->section = sec;
    return;
  }
  SectionTable* newEntry = new SectionTable();
  newEntry->section = sec;
  while (curr->nextEntry!=nullptr)
  {
    curr = curr->nextEntry;
  }
  
  curr->nextEntry = newEntry;
  
}