#pragma once
#include "./SymbolTableEntry.hpp"
#include  "./Section.hpp"

class SymbolTableEntry;
class Section;
class SymbolTable{
public:
  SymbolTable();
  void declareSymbolGlobal(std::string symbol,int isExtern ,Section* currentSection);
  SymbolTableEntry* declareSection(std::string symbol,Section* currentSection);
  void printSymbolTable();
  SymbolTableEntry* getFirstEntry();
  std::string getSymbolNameOfIndex(unsigned int idx);
  int getValueBySymbolName(std::string name);
  SymbolTableEntry* getEntryBySymbolName(std::string name);
  SymbolTableEntry* defineSymbolLocal(std::string symbol, Section* currentSection);
  SymbolTableEntry* declareSymbolLocal(std::string symbol, Section* currentSection,bool isIns,bool isAbs);
  int getTableSize();
  void addEntry(SymbolTableEntry* entry);
private:
  SymbolTableEntry* firstEntry;
  int indexCounter;
  int size;

};