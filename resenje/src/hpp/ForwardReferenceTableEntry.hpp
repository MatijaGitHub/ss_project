#pragma once
#include "./Section.hpp"

class Section;
class ForwardReferenceTableEntry{
  public:
  ForwardReferenceTableEntry(int p,Section* sec,bool isAbs);
  void putForwardReferenceEntry(int p,Section* sec,bool isAbs);
  int getPatch();
  Section* getAtSection();
  ForwardReferenceTableEntry* getNextEntry();
  bool isAbsoluteAddressing();
  private:
  bool isAbs;
  int patch;
  Section* atSection;
  ForwardReferenceTableEntry* nextEntry; 
};