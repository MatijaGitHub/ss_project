#include "../hpp/Emulator.hpp"


Emulator::Emulator(){
  this->memory = (unsigned char*)malloc(USHRT_MAX + 1);
  this->working = false;
  this->psw = 0;
}
void Emulator::init(){
    this->registers[PC_REG] = *(SYSTEM_REGISTER*)(this->memory + 0);
    opCodes[0b00000000] = &haltInstruction;
    opCodes[0b00010000] = &intInstruction;
    opCodes[0b00100000] = &iretInstruction;
    opCodes[0b00110000] = &callInstruction;
    opCodes[0b01000000] = &retInstruction;
    opCodes[0b01010000] = &jmpInstruction;
    opCodes[0b01010001] = &jeqInstruction;
    opCodes[0b01010010] = &jneInstruction;
    opCodes[0b01010011] = &jgtInstruction;
    opCodes[0b01100000] = &xchgInstruction;
    opCodes[0b01110000] = &addInstruction;
    opCodes[0b01110001] = &subInstruction;
    opCodes[0b01110010] = &mulInstruction;
    opCodes[0b01110011] = &divInstruction;
    opCodes[0b01110100] = &cmpInstruction;
    opCodes[0b10000000] = &notInstruction;
    opCodes[0b10000001] = &andInstruction;
    opCodes[0b10000010] = &orInstruction;
    opCodes[0b10000011] = &xorInstruction;
    opCodes[0b10000100] = &testInstruction;
    opCodes[0b10010000] = &shlInstruction;
    opCodes[0b10010001] = &shrInstruction;
    opCodes[0b10100000] = &loadInstruction;
    opCodes[0b10110000] = &storeInstruction;
    addressModes[0b0000] = IMMED_ADR;
    addressModes[0b0001] = REGDIR_ADR;
    addressModes[0b0010] = REGIND_ADR;
    addressModes[0b0011] = REGIND16_ADR;
    addressModes[0b0100] = MEM_ADR;
    addressModes[0b0101] = REGDIR16_ADR;
    upModes[0b0000] = NO_UPDATE;
    upModes[0b0001] = PRE_DEC;
    upModes[0b0010] = PRE_INC;
    upModes[0b0011] = POST_DEC;
    upModes[0b0100] = POST_INC;
}
void Emulator::start(std::string inputFile){
  loadIntoMemory(inputFile);
  working = true;
  init();
  while (working)
  {
    unsigned char opCode = memory[(SYSTEM_REGISTER)(registers[PC_REG])];
    if(opCodes.find(opCode) == opCodes.end()){
        this->registers[PC_REG]++;
        this->intr_enabled[1] = 1;
    }
    else{
        opCodes[opCode]();
    }
    handleInterrupts();
  }
  
}
void Emulator::handleInterrupts(){

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


    void Emulator::haltInstruction(){
      this->working = false;
      this->registers[PC_REG]++;
    }
    void Emulator::intInstruction(){

    }
    void Emulator::iretInstruction();
    void Emulator::callInstruction();
    void Emulator::retInstruction();
    void Emulator::jmpInstruction();
    void Emulator::jeqInstruction();
    void Emulator::jneInstruction();
    void Emulator::jgtInstruction();
    void Emulator::loadInstruction(){
      unsigned char registerByte = (SYSTEM_REGISTER)(this->registers[PC_REG + 1]);
      unsigned char addressByte = (SYSTEM_REGISTER)(this->registers[PC_REG + 2]);

    }
    void Emulator::storeInstruction();
    void Emulator::xchgInstruction();
    void Emulator::addInstruction();
    void Emulator::subInstruction();
    void Emulator::mulInstruction();
    void Emulator::divInstruction();
    void Emulator::cmpInstruction();
    void Emulator::notInstruction();
    void Emulator::andInstruction();
    void Emulator::orInstruction();
    void Emulator::xorInstruction();
    void Emulator::testInstruction();
    void Emulator::shlInstruction();
    void Emulator::shrInstruction();