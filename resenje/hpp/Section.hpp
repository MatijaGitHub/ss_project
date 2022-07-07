#pragma once
#include <string>
#include "./SymbolTableEntry.hpp"
#include "./RelocationTable.hpp"
#include "./SymbolTable.hpp"
#include <iomanip>

class SymbolTable;
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
  void patchContent(unsigned long content, int location, bool isInstruction);
  void readContent();
  void printRelocationTable(SymbolTable* symbolTable);
  int size;
  RelocationTable* myRelocationTable;

};