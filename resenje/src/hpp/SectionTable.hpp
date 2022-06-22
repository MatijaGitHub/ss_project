#pragma once
#include "./Section.hpp"

class Section;
class SectionTable{
public:
SectionTable();
Section* getSection();
SectionTable* getNextEntry();
void setSection(Section* sec);
void setNextEntry(SectionTable* nxt);
void addSectionToTail(Section* sec);
void printSectionTable();
void printRelocationTablesForAllSections(SymbolTable* symTab);
private:
Section* section;
SectionTable* nextEntry;
};