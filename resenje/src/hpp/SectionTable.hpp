#pragma once
#include "./Section.hpp"


class SectionTable{
public:
SectionTable();
Section* getSection();
SectionTable* getNextEntry();
void setSection(Section* sec);
void setNextEntry(SectionTable* nxt);
private:
Section* section;
SectionTable* nextEntry;
};