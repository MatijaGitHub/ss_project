#include "../hpp/Assembler.hpp"
#include "../hpp/SymbolTableEntry.hpp"
#include "../hpp/ForwardReferenceTableEntry.hpp"
#include "../hpp/RelocationTableEntry.hpp"

extern int yyparse();
extern FILE* yyin;

int Assembler::init(){
  yyin = fopen(this->inputFile.c_str(),"r");
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
int Assembler::firstPass(){
    Line* currLine = Lines::getHead();
    while(currLine!=nullptr){
      if(currLine->getDirective()){
        this->handleDirective(currLine->getDirective());
      }

      currLine = currLine->getNext();
    }
    return 0;
}

void Assembler::handleDirective(Directive* directive){
    printf("%s",directive->getDirNameString().c_str());
}

int Assembler::assemble(){
  this->init();
  return this->firstPass();
}