#include "../hpp/RelocationTableEntry.hpp"



  RelocationTableEntry::RelocationTableEntry(){}
  RelocationTableEntry::RelocationTableEntry(int symbol,long offset,int addend,RelocationType type){
    this->mySymbol = symbol;
    this->nextEntry = nullptr;
    this->offset = offset;
    this->addend = addend;
    this->type = type;
  }
  std::string RelocationTableEntry::getTypeName(){
    switch (this->type)
    {
    case 0:
      return "R_X86_64_32";
     case 1:
      return "R_X86_64_32S";
     case 2:
      return "R_X86_64_PLT32";
     case 3:
      return "R_X86_64_PC32";
    
    default:
      return "NO_TYPE";
    }
  }