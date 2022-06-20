#pragma once
#include <string>
#include "./SymbolTableEntry.hpp"


class Section{
public:
  Section();
  SymbolTableEntry * myEntry;
  std::string sectionName;
  std::string sectionContent;
  int locationCounter;

};