#pragma once
#include "./RelocationTableEntry.hpp"

class RelocationTableEntry;
class RelocationTable{
  public:
  RelocationTable();
  RelocationTableEntry* getFirstEntry();
  void addEntry(RelocationTableEntry* newEntry);
  RelocationTableEntry* getEntryByOffset(long offset);
  int getRelocationTableSize();
  private:
  RelocationTableEntry* firstEntry;
  int size;
};