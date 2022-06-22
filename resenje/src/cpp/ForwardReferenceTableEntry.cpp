#include "../hpp/ForwardReferenceTableEntry.hpp"


 ForwardReferenceTableEntry::ForwardReferenceTableEntry(int p,Section* sec,bool isAbs){
  this->patch = p;
  this->atSection = sec;
  this->nextEntry = nullptr;
  this->isAbs = isAbs;
 }
  void ForwardReferenceTableEntry::putForwardReferenceEntry(int p,Section* sec,bool isAbs){
    ForwardReferenceTableEntry* entry = new ForwardReferenceTableEntry(p,sec,isAbs);
    ForwardReferenceTableEntry* tail = this;
    while(tail->nextEntry != nullptr) tail = tail->nextEntry;
    tail->nextEntry = entry;
  }
  int ForwardReferenceTableEntry::getPatch(){
    return this->patch;
  }
  ForwardReferenceTableEntry* ForwardReferenceTableEntry::getNextEntry(){
    return this->nextEntry;
  }

  Section* ForwardReferenceTableEntry::getAtSection(){
    return this->atSection;
  }
  bool ForwardReferenceTableEntry::isAbsoluteAddressing(){
    return this->isAbs;
  }