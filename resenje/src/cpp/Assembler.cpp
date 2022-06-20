#include "../hpp/Assembler.hpp"
#include "../hpp/SymbolTableEntry.hpp"

extern int yyparse();
extern FILE* yyin;

int Assembler::init(){
  yyin = fopen("test.s","r");
  int ret = yyparse();
  fclose(yyin);
  return ret;
}

void Assembler::reset(){
  Lines::initLines();
}
Assembler::Assembler(std::string input){
  this->inputFile = input;
  this->outputFile = "defaultOutput.o";
}
Assembler::Assembler(std::string input, std::string output){
  this->inputFile = input;
  this->outputFile = output;
}