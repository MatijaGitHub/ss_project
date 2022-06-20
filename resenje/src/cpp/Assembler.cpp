#include "../hpp/Assembler.hpp"


extern int yyparse();
extern FILE* yyin;

int Assembler::init(){
  yyin = fopen(this->inputFile.c_str(),"r");
  int ret = yyparse();
  fclose(yyin);
  this->mySymbolTable = new SymbolTable();
  this->currentSection = nullptr;
  this->sectionTable = new SectionTable();
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
      if(currLine->getLabel()){
        this->handleLabel(currLine->getLabel());
      }
      if(currLine->getInstruction()){
        this->handleInstruction(currLine->getInstruction());
      }
      if(currLine->getDirective()){
        this->handleDirective(currLine->getDirective());
      }
      currLine = currLine->getNext();
    }
    return 0;
}

void Assembler::handleDirective(Directive* directive){
    switch (directive->getDirectiveName())
    {
    case 0:
      {
        declareSymbolsGlobal(directive->getSymLitList());
        break;
      }
    case 2:
      {
        this->currentSection = new Section();
        this->currentSection->sectionName = directive->getString();
        this->currentSection->myEntry = this->mySymbolTable->declareSymbolLocal(directive->getString(),1);
      }
    default:
      {
        printf("Directive not defined\n");
        break;
      }
    }
}
void Assembler::handleLabel(Label* label){

}
void Assembler::handleInstruction(Instruction* ins){

}

int Assembler::assemble(){
  this->init();
  int res =  this->firstPass();
  if(mySymbolTable){
      mySymbolTable->printSymbolTable();
  }
  else{
      printf("Symbol table is NULL\n");
  }
  return res;
  
}

 void Assembler::declareSymbolsGlobal(Symbol_Literal_List* globalSymbolList){
      std::string* symbol = globalSymbolList->popSymbol();
      while(symbol!=nullptr){
        this->getSymbolTable()->declareSymbolGlobal(*symbol,currentSection);
        symbol = globalSymbolList->popSymbol();
      }
 }
 SymbolTable* Assembler::getSymbolTable(){
    return this->mySymbolTable;
 }
