#pragma once

class ForwardReferenceTableEntry{
  public:
  ForwardReferenceTableEntry(int p);
  void putForwardReferenceEntry(int p);
  int getPatch();
  ForwardReferenceTableEntry* getNextEntry();
  private:
  int patch;
  ForwardReferenceTableEntry* nextEntry; 
};