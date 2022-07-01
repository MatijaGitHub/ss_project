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
      elfFile >> sec->size;
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
      std::pair<int,std::string> secData;
      secData.first = sec->size;
      secData.second = sec->sectionContent;
      this->sectionContents[sec->sectionName].push_back(secData);

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
    printf("NOT ALL EXTERN SYMBOLS DEFINED!\n");
    exit(-1);
  }
}
void Linker::placeSection(std::string command){
  long lastLoc = command.find_last_of('@');
  std::string nameOfSection = command.substr(7, lastLoc - 7);
  std::string placement = command.substr(lastLoc + 1);
  int placementValue;
  if(placement.at(1) == 'x') placementValue = std::stoi(placement,nullptr,16);
  else placementValue = std::stoi(placement);
  if(placementValue < 0 || placementValue >= USHRT_MAX){
    printf("INVALID START ADDRESS!\n");
    exit(-1);
  }
  unsigned short convert = placementValue;
  this->placedSections[nameOfSection] = convert;
}

 void Linker::map(){
    unsigned short maxAddress = 0;
    for(std::pair<std::string,unsigned short> placedSection : this->placedSections){
        std::string secName = placedSection.first;
        if(sectionContents.find(secName) == sectionContents.end()) continue;
        unsigned short secBegin = placedSection.second;
        unsigned short secSize = 0;
        for(std::pair<int,std::string> size : sectionContents[secName]){
          secSize += size.first;
        }
        checkIfPlacementPossible(secBegin, secBegin + secSize);
        mappedSections[secName] = secBegin;
        if(secBegin + secSize > maxAddress) maxAddress = secBegin + secSize;
    }
    for(std::pair<std::string, std::vector<std::pair<int,std::string>>> section : sectionContents){
      std::string secName = section.first;
      std::vector<std::pair<int,std::string>> content = section.second;
      if(mappedSections.find(secName) != mappedSections.end()) continue;
      unsigned short secSize = 0;
      for(std::pair<int,std::string> size : content){
        secSize += size.first;
      }
      mappedSections[secName] = maxAddress;
      maxAddress += secSize;
    }
 }

 void Linker::checkIfPlacementPossible(unsigned short min,unsigned short max){
    for(std::pair<std::string,unsigned short> allocatedSection : mappedSections){
      if(allocatedSection.second >= min && allocatedSection.second < max){
        printf("BAD ALLOCATION, SECTIONS INTERSECTED IN MEMORY!\n");
        exit(-1);
      }
    }
 }


 void Linker::link(std::vector<std::string> files){
  readELFS(files);
  map();
  for(std::pair<std::string,unsigned short> section : mappedSections){
    printf("SEKCIJA: %s MAPIRANA NA ADRESU: %d\n",section.first.c_str(),section.second);
  }
  resolveSymbols();
  exoneration();
    
 }

void Linker::resolveSymbols(){

}
void Linker::exoneration(){

}