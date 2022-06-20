#pragma once
#include "../hpp/SymbolTableEntry.hpp"
class SymbolTable{
public:
  SymbolTable();
  void declareSymbolGlobal(std::string symbol);
private:
  SymbolTableEntry* firstEntry;
  int indexCounter;

};