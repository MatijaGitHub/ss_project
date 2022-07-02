#include "../hpp/Emulator.hpp"


Emulator::Emulator(){
  this->memory = (unsigned char*)malloc(USHRT_MAX + 1);
  this->working = false;
  this->intr_enabled = 0;
  this->psw = 0;
}

void Emulator::start(std::string inputFile){
  this->loadIntoMemory(inputFile);
  working = true;
  while (working)
  {
    //WORKING
  }
  
}

unsigned char getByteAtPosition(std::string line, int position){
  std::string byte = line.substr(position*3,2);
  unsigned char result =std::stoul(byte, nullptr, 16);
  return result;
}
void Emulator::loadIntoMemory(std::string inputFile){
  std::ifstream hexFile;
  hexFile.open(inputFile);
  std::string line = " ";
  while (true)
  {
    std::getline(hexFile,line);
    if(line == "")break;
    int address = std::stoi(line.substr(0,4),nullptr,16);
    std::string content = line.substr(6);
    for(int i = 0; i < (content.size()+1)/3; i++){
      this->memory[address + i] = getByteAtPosition(content,i);
    }
    
   
  }
  
  
}