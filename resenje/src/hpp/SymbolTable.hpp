#pragma once
#include "./SymbolTableEntry.hpp"
#include  "./Section.hpp"
#include  "./ForwardReferenceTableEntry.hpp"
class SymbolTable{
public:
  SymbolTable();
  void declareSymbolGlobal(std::string symbol,int isExtern ,Section* currentSection);
  SymbolTableEntry* declareSymbolLocal(std::string symbol,int isSection,Section* currentSection);
  void printSymbolTable();
  SymbolTableEntry* getFirstEntry();
  std::string getSymbolNameOfIndex(unsigned int idx);
  int getValueBySymbolName(std::string name);
private:
  SymbolTableEntry* firstEntry;
  int indexCounter;

};