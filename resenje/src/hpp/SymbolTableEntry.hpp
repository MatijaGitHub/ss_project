#pragma once
#include <string>
#include "./RelocationTableEntry.hpp"


class SymbolTableEntry{
public:
  unsigned index;
  unsigned long value;
  unsigned size;
  std::string type;
  char bind;
  int belongsTo; //Has value -1 if UND
  std::string name;
  RelocationTableEntry * myRelocationTable;
};