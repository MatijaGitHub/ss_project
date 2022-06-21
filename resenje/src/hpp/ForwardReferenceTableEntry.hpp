#pragma once
#include "./Section.hpp"

class Section;
class ForwardReferenceTableEntry{
  public:
  ForwardReferenceTableEntry(int p,Section* sec);
  void putForwardReferenceEntry(int p,Section* sec);
  int getPatch();
  Section* getAtSection();
  ForwardReferenceTableEntry* getNextEntry();
  private:
  int patch;
  Section* atSection;
  ForwardReferenceTableEntry* nextEntry; 
};