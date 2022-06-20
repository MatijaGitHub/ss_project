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