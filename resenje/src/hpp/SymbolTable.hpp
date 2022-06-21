#pragma once
#include "./SymbolTableEntry.hpp"
#include  "./Section.hpp"
#include  "./ForwardReferenceTableEntry.hpp"
class SymbolTable{
public:
  SymbolTable();
  void declareSymbolGlobal(std::string symbol,int isExtern ,Section* currentSection);
  SymbolTableEntry* declareSection(std::string symbol,int isSection,Section* currentSection);
  void printSymbolTable();
  SymbolTableEntry* getFirstEntry();
  std::string getSymbolNameOfIndex(unsigned int idx);
  int getValueBySymbolName(std::string name);
  SymbolTableEntry* getEntryBySymbolName(std::string name);
  SymbolTableEntry* defineSymbolLocal(std::string symbol, Section* currentSection);
private:
  SymbolTableEntry* firstEntry;
  int indexCounter;

};