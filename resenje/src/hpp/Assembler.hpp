#pragma once
#include "../../misc/hpp/Lines.hpp"
#include "./SymbolTable.hpp"
#include "./Section.hpp"
#include "./SymbolTableEntry.hpp"
#include "./ForwardReferenceTableEntry.hpp"
#include "./RelocationTableEntry.hpp"
#include "./SectionTable.hpp"
#include <string>

class Assembler{
public:
  Assembler(std::string input);
  Assembler(std::string input, std::string output);
  int assemble();
  SymbolTable* getSymbolTable();
protected:
  std::string inputFile;
  std::string outputFile;
  SymbolTable* mySymbolTable;
  Section* currentSection;
  SectionTable* sectionTable;
private:
  int init();
  void reset();
  int firstPass();
  void handleDirective(Directive* directive);
  void handleLabel(Label* label);
  void handleInstruction(Instruction* ins);
  void declareSymbolsGlobal(Symbol_Literal_List* globalSymbolList);
  
};