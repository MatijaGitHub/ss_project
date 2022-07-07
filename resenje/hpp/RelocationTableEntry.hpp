#pragma once
#include "./Section.hpp"
#include <string>

enum RelocationType{
  R_X86_64_32,R_X86_64_32S,R_X86_64_PLT32,R_X86_64_PC32
};
class Section;
class RelocationTableEntry{
public: 
  RelocationTableEntry();
  RelocationTableEntry(int symbol,long offset,int addend,RelocationType type);
  std::string getTypeName();
  long offset;
  RelocationType type;
  int mySymbol;
  std::string symbolName;
  int addend;
  int belongsToSectionIndex;
  RelocationTableEntry* nextEntry;
};