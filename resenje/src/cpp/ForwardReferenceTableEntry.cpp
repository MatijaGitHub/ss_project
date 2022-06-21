#include "../hpp/ForwardReferenceTableEntry.hpp"


 ForwardReferenceTableEntry::ForwardReferenceTableEntry(int p,Section* sec){
  this->patch = p;
  this->atSection = sec;
  this->nextEntry = nullptr;
 }
  void ForwardReferenceTableEntry::putForwardReferenceEntry(int p,Section* sec){
    ForwardReferenceTableEntry* entry = new ForwardReferenceTableEntry(p,sec);
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