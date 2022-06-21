#pragma once
#include <string>
#include "./SymbolTableEntry.hpp"
#include "./RelocationTable.hpp"
#include <iomanip>

class SymbolTableEntry;
class RelocationTable;
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
  void patchContent(unsigned long content, int location);
  void readContent();
  RelocationTable* myRelocationTable;

};