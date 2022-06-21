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
        this->currentSection->myEntry = this->mySymbolTable->declareSection(directive->getString(),currentSection);
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
    case 5:
      {
        initializeSpaceForString(directive->getString(),currentSection);
        break;
      }
    case 7:
      {
        endCurrentSection();
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
    
     this->mySymbolTable->defineSymbolLocal(label->getLabel(),this->currentSection);
}
void Assembler::handleInstruction(Instruction* ins){
    int length = ins->getInstructionLength();
    AddressMode adr = ins->getAddressMode();
    for(int i = 0; i < length; i++){
      //printf("%s ",ins->generateByteOfInstructions(i).c_str());
      this->currentSection->locationCounter++;
      this->currentSection->writeOneByteContent(ins->generateByteOfInstructions(i));
    }
    
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
  int size = 0;
  std::string* symbol = symbolsAndLiterals->popSymbol();
  int* literal = symbolsAndLiterals->popLiteral();
  while(symbol!=nullptr){
    SymbolTableEntry* symbolEntry = this->mySymbolTable->declareSymbolLocal(*symbol,currentSection);
    if(!symbolEntry->defined || currentSection->myEntry->index!=symbolEntry->index){
      
    }
    currentSection->locationCounter+=2;
    size+=2;
    int value = this->mySymbolTable->getValueBySymbolName(*symbol);
    currentSection->writeTwoByteContent(turnIntTo2Byte(this->mySymbolTable->getValueBySymbolName(*symbol)));
    symbol = symbolsAndLiterals->popSymbol();
  }
  while(literal!=nullptr){
    size+=2;
    currentSection->locationCounter+=2;
    currentSection->writeTwoByteContent(turnIntTo2Byte(*literal));
    literal = symbolsAndLiterals->popLiteral();
  }
  this->mySymbolTable->getEntryBySymbolName(currentSection->sectionName)->size+=size;
}
void Assembler::initializeSpaceWithZeros(int literal,Section* currentSection){
  int size = 0;
  for(int i = 0;i < literal;i++){
    currentSection->locationCounter++;
    size++;
    currentSection->writeOneByteContent("00");
  }
  this->mySymbolTable->getEntryBySymbolName(currentSection->sectionName)->size+=size;
}
void Assembler::initializeSpaceForString(std::string string,Section* currentSection){
  int size = 0;
  std::stringstream stream;
  int counter = -1;
  int length = string.length();
  bool isNewLine = false;
  for(char& c : string){
    counter++;
    if(counter == 0 || counter == length - 1) continue;
    if(isNewLine){
      isNewLine = false;
      continue;
    }
    currentSection->locationCounter++;
    size++;
    if(string.at(counter) == '\\' && string.at(counter+1) == 'n'){
      currentSection->writeOneByteContent("0a");
      isNewLine = true;
      continue;
    }
    stream << std::setfill ('0') << std::setw(sizeof(short))
           << std::hex << (int)c;
    currentSection->writeOneByteContent(stream.str());
    stream.str("");
    
    
  }
  currentSection->locationCounter++;
  size++;
  currentSection->writeOneByteContent("00");
  this->mySymbolTable->getEntryBySymbolName(currentSection->sectionName)->size+=size;

}
std::string Assembler::turnIntTo2Byte(int twobyte){
  std::stringstream stream;
  stream << std::setfill ('0') << std::setw(sizeof(short)) 
         << std::hex << twobyte;
  return stream.str();
  
}

void Assembler::endCurrentSection(){
  this->currentSection = nullptr;
}

