#pragma once
#include "./SymbolTableEntry.hpp"
#include  "./Section.hpp"
class SymbolTable{
public:
  SymbolTable();
  void declareSymbolGlobal(std::string symbol, Section* currentSection);
  SymbolTableEntry* declareSymbolLocal(std::string symbol,int isSection);
  void printSymbolTable();
  SymbolTableEntry* getFirstEntry();
  std::string getSymbolNameOfIndex(unsigned int idx);
private:
  SymbolTableEntry* firstEntry;
  int indexCounter;

};