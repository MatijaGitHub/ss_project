#pragma once
#include <string>
#include "./SymbolTableEntry.hpp"
#include "./RelocationTable.hpp"


class Section{
public:
  Section();
  SymbolTableEntry * myEntry;
  std::string sectionName;
  std::string sectionContent;
  int locationCounter;
  int sectionContentCounter;
  void writeTwoByteContent(std::string twobyte);
  void writeOneByteContent(std::string byte);
  void readContent();
  RelocationTable* myRelocationTable;

};