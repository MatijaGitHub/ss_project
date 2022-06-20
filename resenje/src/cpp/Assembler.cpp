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
        declareSymbolsGlobal(directive->getSymLitList(),0);
        break;
      }
    case 1:
      {
        declareSymbolsGlobal(directive->getSymLitList(),1);
        break;
      }
    case 2:
      {
        this->currentSection = new Section();
        this->currentSection->sectionName = directive->getString();
        this->currentSection->myEntry = this->mySymbolTable->declareSymbolLocal(directive->getString(),1,currentSection);

        this->sectionTable->addSectionToTail(this->currentSection);
     
        break;
      }
    case 3:
      {
        initializeSpace(directive->getSymLitList(),currentSection);
        break;
      }
    case 4:
      {
        initializeSpaceWithZeros(directive->getLiteral(),currentSection);
        break;
      }
    default:
      {
        printf("Directive %s not defined\n" , directive->getDirNameString().c_str());
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
      printf("Symbol table is NULL!\n");
  }
  if(sectionTable){
    sectionTable->printSectionTable();
  }
  else{
    printf("Section table is NULL!\n");
  }
  return res;
  
}

 void Assembler::declareSymbolsGlobal(Symbol_Literal_List* globalSymbolList,int isExtern){
      std::string* symbol = globalSymbolList->popSymbol();
      while(symbol!=nullptr){
        this->getSymbolTable()->declareSymbolGlobal(*symbol,isExtern,currentSection);
        symbol = globalSymbolList->popSymbol();
      }
 }
 SymbolTable* Assembler::getSymbolTable(){
    return this->mySymbolTable;
 }
void Assembler::initializeSpace(Symbol_Literal_List* symbolsAndLiterals,Section* currentSection){
  std::string* symbol = symbolsAndLiterals->popSymbol();
  int* literal = symbolsAndLiterals->popLiteral();
  while(symbol!=nullptr){
    currentSection->locationCounter+=2;
    int value = this->mySymbolTable->getValueBySymbolName(*symbol);
    currentSection->writeTwoByteContent(turnIntTo2Byte(this->mySymbolTable->getValueBySymbolName(*symbol)));
    symbol = symbolsAndLiterals->popSymbol();
  }
  while(literal!=nullptr){
    currentSection->locationCounter+=2;
    currentSection->writeTwoByteContent(turnIntTo2Byte(*literal));
    literal = symbolsAndLiterals->popLiteral();
  }
}
void Assembler::initializeSpaceWithZeros(int literal,Section* currentSection){
  for(int i = 0;i < literal;i++){
    currentSection->locationCounter++;
    currentSection->writeOneByteContent("00");
  }
}
std::string Assembler::turnIntTo2Byte(int twobyte){
  printf("%d\n",twobyte);
  std::stringstream stream;
  stream << std::setfill ('0') << std::setw(sizeof(short)) 
         << std::hex << twobyte;
  return stream.str();
  
}
