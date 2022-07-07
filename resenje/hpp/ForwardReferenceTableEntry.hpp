#pragma once
#include "./Section.hpp"

class Section;
class ForwardReferenceTableEntry{
  public:
  ForwardReferenceTableEntry(int p,Section* sec,bool isAbs,bool isIns);
  void putForwardReferenceEntry(int p,Section* sec,bool isAbs,bool isIns);
  int getPatch();
  Section* getAtSection();
  ForwardReferenceTableEntry* getNextEntry();
  bool isAbsoluteAddressing();
  bool isInstructionPatch();
  private:
  bool isIns;
  bool isAbs;
  int patch;
  Section* atSection;
  ForwardReferenceTableEntry* nextEntry; 
};