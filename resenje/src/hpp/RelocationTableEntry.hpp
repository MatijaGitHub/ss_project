#pragma once
#include "./Section.hpp"
#include <string>


class RelocationTableEntry{
public: 
  RelocationTableEntry();
  RelocationTableEntry(Section* section,int symbol,int type);
  long offset;
  std::string type;
  int mySymbol;
  int addend;
  RelocationTableEntry* nextEntry;
};