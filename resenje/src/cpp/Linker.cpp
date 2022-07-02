#include "../hpp/Linker.hpp"


Linker::Linker(){
  this->symbolTable = new SymbolTable();
  this->toHex = false;
  this->outputFile = "defaultOutput.hex";
}
void Linker::setOutput(std::string out){
  this->outputFile = out;
}
void Linker::setToHex(){
  this->toHex = true;
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
    elfFile >> newSymbol->belongsToSection;
    skipLines(2,&elfFile);
    elfFile >> newSymbol->bind;
    skipLines(2,&elfFile);
    elfFile >> newSymbol->type;
    skipLines(2,&elfFile);
    elfFile >> newSymbol->size;
    skipLines(2,&elfFile);
    elfFile >> newSymbol->value;
    skipLines(1,&elfFile);
    if(newSymbol->bind == 'g' && newSymbol->belongsToSection != "UND"){
        checkIfSymbolIsDefined(newSymbol->name);
        if(sectionAppearances.find(newSymbol->belongsToSection) == sectionAppearances.end()){
          newSymbol->belongsToSectionIndex = 0;
        }else{
          newSymbol->belongsToSectionIndex = sectionAppearances[newSymbol->belongsToSection];
        }
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
      if(sectionAppearances.find(sec->sectionName) == sectionAppearances.end()){
        sectionAppearances[sec->sectionName] = 1;
        orderOfSections.push_back(sec->sectionName);
      }
      else{
        sectionAppearances[sec->sectionName]++;
      }

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
    newEntry->belongsToSectionIndex = sectionAppearances[sectionName] - 1;
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
  SymbolTableEntry* entry = this->symbolTable->getFirstEntry();
  while(entry!=nullptr){
    this->externSymbols.erase(entry->name);
    entry = entry->nextEntry;
  }
    if(this->externSymbols.size() > 0){
    printf("THE FOLLOWING SYMBOLS ARE NOT DEFINED:\n");
    for(std::set<std::string>::iterator begin = this->externSymbols.begin();begin!=this->externSymbols.end();begin++){
      printf("%s\n",(*begin).c_str());
    }
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
        checkIfPlacementPossible(secBegin, secBegin + secSize,secName);
        mappedSections[secName] = secBegin;
        if(secBegin + secSize > maxAddress) maxAddress = secBegin + secSize;
    }
    for(std::string sectionName : orderOfSections){
      
            std::vector<std::pair<int,std::string>> content = sectionContents[sectionName];
            std::string secName = sectionName;
            if(mappedSections.find(secName) != mappedSections.end()) continue;
            unsigned short secSize = 0;
            for(std::pair<int,std::string> size : content){
              secSize += size.first;
            }
            mappedSections[secName] = maxAddress;
            maxAddress += secSize;
       
    }
   
 }

 void Linker::checkIfPlacementPossible(unsigned short min,unsigned short max, std::string sectionName){
    for(std::pair<std::string,unsigned short> allocatedSection : mappedSections){
      if(allocatedSection.second >= min && allocatedSection.second < max){
        printf("BAD ALLOCATION, SECTIONS %s AND %s ARE INTERSECTED IN MEMORY!\n",sectionName.c_str(),allocatedSection.first.c_str());
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
  this->symbolTable->printSymbolTable();
  exoneration();
  if(this->toHex){
    hex();
  }
  
    
 }

void Linker::resolveSymbols(){
  SymbolTableEntry* entry = this->symbolTable->getFirstEntry();
  while (entry != nullptr)
  {
    unsigned short fileOffset = 0;
    for(int i = 0; i < entry->belongsToSectionIndex ; i++){
      fileOffset+=sectionContents[entry->belongsToSection][i].first;
    }
    entry->value = entry->value + mappedSections[entry->belongsToSection] + fileOffset;
    entry = entry->nextEntry;
  }
  
}
void Linker::exoneration(){
  for(std::pair<std::string,RelocationTable*> relocTable : this->relocationTables){
    std::string secName = relocTable.first;
    RelocationTableEntry* entry = relocTable.second->getFirstEntry();
    while (entry != nullptr)
    {
      std::string content = sectionContents[secName].at(entry->belongsToSectionIndex).second;
      Section* section = new Section();
      section->sectionContent = content;
      unsigned long value;
      SymbolTableEntry* symbol = symbolTable->getEntryBySymbolName(entry->symbolName);
      if(symbol == nullptr){
        value = mappedSections[entry->symbolName];
      }
      else{
        value = symbol->value;
      }
      unsigned long toReplace = entry->addend + value;
      if(entry->type == R_X86_64_PLT32 || entry->type == R_X86_64_PC32){
        unsigned short fileOffset = 0;
        for(int i = 0; i < entry->belongsToSectionIndex ; i++){
          fileOffset+=sectionContents[secName][i].first;
        }
        unsigned long sub = entry->offset + mappedSections[secName] + fileOffset;
        toReplace-=sub; 
      }
      
      section->patchContent(toReplace,entry->offset,entry->type != R_X86_64_32);
      sectionContents[secName].at(entry->belongsToSectionIndex).second = section->sectionContent;
      entry = entry->nextEntry;
    }
    
  }
}
bool cmp(std::pair<std::string, unsigned short>& a,
         std::pair<std::string, unsigned short>& b)
{
    return a.second < b.second;
}
std::vector<std::pair<std::string, unsigned short>> sort(std::unordered_map<std::string, unsigned short>& M)
{
    std::vector<std::pair<std::string, unsigned short> > A;
    for (auto& it : M) {
        A.push_back(it);
    }
    sort(A.begin(), A.end(), cmp);
    return A;
}
std::string replaceStringWith(char from,char to,std::string str){
  for(int i = 0; i<str.size();i++){
    if(str.at(i) == from){
      str[i] = to;
    }
  }
  return str;
}
std::string addAddresses(std::string content, int* currentAdr, int* counter){
      int at = 0;
      while(at < content.size()){
        if(*counter % 8 == 0){
          std::stringstream stream;
          stream << std::setfill ('0') << std::setw(sizeof(int)) 
                << std::hex << *currentAdr;
          std::string adr = stream.str();
          stream.str("");
          adr+=": ";
          
          content.insert(at,adr);
          if(at!=0) content[at-1] = '\n';
          *currentAdr+=8;
          at+=30;
        }
        else{
          at+=((8-(*counter%8))*3);
          *currentAdr+=(8-(*counter%8));
          *counter = 0;
        }
      }
      if(at!=content.size()){
        *currentAdr-=((at-content.size())/3);
        *counter+=8;
        *counter-=((at-content.size())/3);
      }
      return content;
    
  


}
void Linker::hex(){
  std::string hexContent = "";
  std::vector<std::pair<std::string, unsigned short>> sorted = sort(mappedSections);
  int counter,startAdr = -1,prev;
  for(std::pair<std::string,unsigned short> pair : sorted){
    std::vector<std::pair<int,std::string>> sectionContent = sectionContents[pair.first];
    prev = startAdr;
    startAdr = pair.second;
    if(prev!=startAdr) counter = 0;
    for(std::pair<int,std::string> content : sectionContent){
      std::string currSection = content.second;
      currSection = replaceStringWith('\t',' ',currSection);
      if(counter%8==0 && prev!=-1) hexContent+="\n";
      hexContent+=addAddresses(replaceStringWith('\n',' ',currSection),&startAdr,&counter);
    }
   
  }
  std::ofstream hexFile;
  hexFile.open(this->outputFile);
  hexFile << hexContent << '\n' << '\n';
  hexFile.close();
}