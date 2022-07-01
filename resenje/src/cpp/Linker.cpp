#include "../hpp/Linker.hpp"


Linker::Linker(){
  this->symbolTable = new SymbolTable();
}

void Linker::readELF(std::string fileName){
  std::ifstream elfFile;
  elfFile.open(fileName);
  skipLines(3,&elfFile);
  elfFile >> this->numOfSymbols;
  skipLines(2,&elfFile);
  elfFile >> this->numOfSections;
  skipLines(2,&elfFile);
  elfFile >> this->numOfRelocations;
  skipLines(4,&elfFile);
  for(int i = 0; i < this->numOfSymbols;i++){
    skipLines(1,&elfFile);
    SymbolTableEntry* newSymbol = new SymbolTableEntry();
    elfFile >> newSymbol->name;
    skipLines(2,&elfFile);
    elfFile >> newSymbol->belongsTo;
    skipLines(2,&elfFile);
    elfFile >> newSymbol->bind;
    skipLines(2,&elfFile);
    elfFile >> newSymbol->type;
    skipLines(2,&elfFile);
    elfFile >> newSymbol->size;
    skipLines(2,&elfFile);
    elfFile >> newSymbol->value;
    skipLines(1,&elfFile);
    if(newSymbol->bind == 'g' && newSymbol->belongsTo != -1){
        checkIfSymbolIsDefined(newSymbol->name);
        this->symbolTable->addEntry(newSymbol);
        this->externSymbols.erase(newSymbol->name);
    }
    else if(newSymbol->bind == 'g'){
      this->externSymbols.insert(newSymbol->name);
      delete newSymbol;
    }
    else{
      delete newSymbol;
    }
  }
  skipLines(3,&elfFile);
  for(int i = 0; i < this->numOfSections;i++){
      skipLines(1,&elfFile);
      Section* sec = new Section();
      elfFile >> sec->sectionName;
      skipLines(2,&elfFile);
      while(true){
        char* byte = (char*)malloc(sizeof(char)*3);
        elfFile.read(byte,2);
        if(byte[0] == '\n' && (byte[1] == 'S' || byte[1] == '/')) break;
        byte[2] = '\0';
        std::string stringByte(byte);
        sec->writeOneByteContent(stringByte);
        delete byte;
        char* dump = (char*)malloc(sizeof(char));
        elfFile.read(dump,1);
      }
      this->sectionContents[sec->sectionName].push_back(sec->sectionContent);

  }
  skipLines(3,&elfFile);
  for(int i = 0; i < this->numOfRelocations; i++){
    skipLines(1,&elfFile);
    RelocationTableEntry* newEntry = new RelocationTableEntry();
    std::string sectionName;
    elfFile >> sectionName;
    skipLines(2,&elfFile);
    elfFile >> newEntry->offset;
    skipLines(2,&elfFile);
    int type;
    elfFile >> type;
    newEntry->type = (RelocationType)type;
    newEntry->nextEntry = nullptr;
    skipLines(2,&elfFile);
    elfFile >> newEntry->symbolName;
    skipLines(2,&elfFile);
    elfFile >> newEntry->addend;
    skipLines(1,&elfFile);
    if(this->relocationTables.find(sectionName) == this->relocationTables.end()){
      this->relocationTables[sectionName] = new RelocationTable();
    }
    this->relocationTables[sectionName]->addEntry(newEntry);
  }


}

void Linker::skipLines(int n , std::ifstream* file){
  std::string dump;
  for(int i = 0; i < n; i++) std::getline(*file,dump);
}

void Linker::checkIfSymbolIsDefined(std::string name){
    SymbolTableEntry* entry = this->symbolTable->getFirstEntry();
    while (entry != nullptr)
    {
      if(entry->name == name){
        printf("SYMBOL %s IS ALREADY DEFINED!\n",entry->name.c_str());
        exit(-1);
      }
      entry = entry->nextEntry;
    }
    
}

void Linker::readELFS(std::vector<std::string> files){
  for(std::string s : files){
    readELF(s);
  }
    if(this->externSymbols.size() > 0){
    printf("NOT ALL EXTERN SYMBOLS DEFINED!");
    exit(-1);
  }
}