#pragma once
#include <string>
#include "./SymbolTableEntry.hpp"


class Section{
public:
  SymbolTableEntry * myEntry;
  std::string sectionContent;
  int locationCounter;

};