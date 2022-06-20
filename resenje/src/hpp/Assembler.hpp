#pragma once
#include "../../misc/hpp/Lines.hpp"
#include "./SymbolTable.hpp"
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
private:
  int init();
  void reset();
  int firstPass();
  void handleDirective(Directive* directive);
  void handleLabel(Label* label);
  void handleInstruction(Instruction* ins);
  void declareSymbolsGlobal(Symbol_Literal_List* globalSymbolList);
};