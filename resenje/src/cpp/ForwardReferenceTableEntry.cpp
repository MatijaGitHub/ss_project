#include "../hpp/ForwardReferenceTableEntry.hpp"


 ForwardReferenceTableEntry::ForwardReferenceTableEntry(int p){
  this->patch = p;
  this->nextEntry = nullptr;
 }
  void ForwardReferenceTableEntry::putForwardReferenceEntry(int p){
    ForwardReferenceTableEntry* entry = new ForwardReferenceTableEntry(p);
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