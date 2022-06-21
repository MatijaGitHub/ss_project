#include "../hpp/RelocationTableEntry.hpp"



  RelocationTableEntry::RelocationTableEntry(){}
  RelocationTableEntry::RelocationTableEntry(Section* section,int symbol,int type){
    this->mySymbol = symbol;
    this->nextEntry = nullptr;
    this->offset = section->locationCounter;
    this->type = "";
    this->type = type == 1?"R_X86_64_32S":this->type;
    this->type = type == 2?"R_X86_64_32S":this->type;
    this->type = type == 3?"R_X86_64_PLT32":this->type;
    this->type = type == 4?"R_X86_64_PC32":this->type;
    
  }