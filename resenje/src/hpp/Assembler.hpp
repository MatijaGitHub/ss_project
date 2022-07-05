#pragma once
#include "../../misc/hpp/Lines.hpp"
#include "./SymbolTable.hpp"
#include "./Section.hpp"
#include "./SymbolTableEntry.hpp"
#include "./ForwardReferenceTableEntry.hpp"
#include "./RelocationTableEntry.hpp"
#include "./SectionTable.hpp"
#include <string>
#include <iomanip>
#include <iostream>
#include <fstream>


class Assembler{
public:
  Assembler(std::string input);
  Assembler(std::string input, std::string output);
  int assemble();
  void objDump();
  SymbolTable* getSymbolTable();
protected:
  std::string inputFile;
  std::string outputFile;
  SymbolTable* mySymbolTable;
  Section* currentSection;
  SectionTable* sectionTable;
  bool endOfAssembling;
private:
  int init();
  void reset();
  int firstPass();
  int backpatch();
  void createELF();
  void handleDirective(Directive* directive);
  void handleLabel(Label* label);
  void handleInstruction(Instruction* ins);
  void declareSymbolsGlobal(Symbol_Literal_List* globalSymbolList,int isExtern);
  void initializeSpace(Symbol_Literal_List* symbolsAndLiterals,Section* currentSection);
  void initializeSpaceWithZeros(int literal,Section* currentSection);
  void initializeSpaceForString(std::string string,Section* currentSection);
  void handleEqu(Expression* exp);
  void endCurrentSection();
  static std::string turnIntTo2Byte(int twobyte);
  
};