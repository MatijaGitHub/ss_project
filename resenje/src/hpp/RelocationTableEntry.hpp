#pragma once
#include <string>


class RelocationTableEntry{
public:
  long offset;
  std::string type;
  int mySymbol;
  int addend;
};