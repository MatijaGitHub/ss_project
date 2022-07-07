#pragma once
#include <string>
#include "./RelocationTableEntry.hpp"
#include "./ForwardReferenceTableEntry.hpp"

class RelocationTableEntry;
class ForwardReferenceTableEntry;
class SymbolTableEntry{
public:
  SymbolTableEntry();
  unsigned index;
  unsigned long value;
  unsigned size;
  std::string type;
  char bind;
  int belongsTo; //Has value -1 if UND
  std::string belongsToSection;
  std::string name;
  RelocationTableEntry * myRelocationTable;
  bool defined;
  int belongsToSectionIndex;
  ForwardReferenceTableEntry * flink;
  SymbolTableEntry *nextEntry;
};