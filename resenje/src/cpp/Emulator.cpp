#include "../hpp/Emulator.hpp"


Emulator::Emulator(){
  this->memory = (unsigned char*)malloc(USHRT_MAX + 1);
  this->working = false;
  this->psw = 0;
}
void Emulator::init(){
    this->registers[PC_REG] = *(SYSTEM_REGISTER*)(this->memory + 0);
    opCodes[0b00000000] = &Emulator::haltInstruction;
    opCodes[0b00010000] = &Emulator::intInstruction;
    opCodes[0b00100000] = &Emulator::iretInstruction;
    opCodes[0b00110000] = &Emulator::callInstruction;
    opCodes[0b01000000] = &Emulator::retInstruction;
    opCodes[0b01010000] = &Emulator::jmpInstruction;
    opCodes[0b01010001] = &Emulator::jeqInstruction;
    opCodes[0b01010010] = &Emulator::jneInstruction;
    opCodes[0b01010011] = &Emulator::jgtInstruction;
    opCodes[0b01100000] = &Emulator::xchgInstruction;
    opCodes[0b01110000] = &Emulator::addInstruction;
    opCodes[0b01110001] = &Emulator::subInstruction;
    opCodes[0b01110010] = &Emulator::mulInstruction;
    opCodes[0b01110011] = &Emulator::divInstruction;
    opCodes[0b01110100] = &Emulator::cmpInstruction;
    opCodes[0b10000000] = &Emulator::notInstruction;
    opCodes[0b10000001] = &Emulator::andInstruction;
    opCodes[0b10000010] = &Emulator::orInstruction;
    opCodes[0b10000011] = &Emulator::xorInstruction;
    opCodes[0b10000100] = &Emulator::testInstruction;
    opCodes[0b10010000] = &Emulator::shlInstruction;
    opCodes[0b10010001] = &Emulator::shrInstruction;
    opCodes[0b10100000] = &Emulator::loadInstruction;
    opCodes[0b10110000] = &Emulator::storeInstruction;
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
        printf("ERROR!\n");
    }
    else{
        (this->*opCodes[opCode])();
    }
    handleInterrupts();
  }
  printf("REGISTER VALUES: r0 := %d, r1 := %d, r2 := %d, r3 := %d, r4 := %d, r5 := %d, r6 := %d, r7 := %d\n",this->registers[0] ,this->registers[1] ,this->registers[2] ,this->registers[3] ,this->registers[4] ,this->registers[5] ,this->registers[6] ,this->registers[7]);
  
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
    void Emulator::iretInstruction(){}
    void Emulator::callInstruction(){}
    void Emulator::retInstruction(){}
    void Emulator::jmpInstruction(){}
    void Emulator::jeqInstruction(){}
    void Emulator::jneInstruction(){}
    void Emulator::jgtInstruction(){}
    void Emulator::loadInstruction(){
      unsigned char registerByte = memory[(SYSTEM_REGISTER)(this->registers[PC_REG]) + 1];
      unsigned char addressByte = memory[(SYSTEM_REGISTER)(this->registers[PC_REG]) + 2];
      unsigned char addressMode = addressByte & 0b00001111;
      unsigned char upMode = (addressByte & 0b11110000) >> 4;
      unsigned char rD = (registerByte & 0b11110000) >> 4;
      unsigned char rS = registerByte & 0b00001111;
      bool isValid = true;
      short* operandDest = nullptr;
      short operand = getOperand(addressMode,upMode,rD,rS,&isValid,&operandDest);
      if(!isValid){
        this->registers[PC_REG] += 3;
        return;
      }
      this->registers[rD] = operand;


    }
    void Emulator::storeInstruction(){
      unsigned char registerByte = memory[(SYSTEM_REGISTER)(this->registers[PC_REG]) + 1];
      unsigned char addressByte = memory[(SYSTEM_REGISTER)(this->registers[PC_REG]) + 2];
      unsigned char addressMode = addressByte & 0b00001111;
      unsigned char upMode = (addressByte & 0b11110000) >> 4;
      unsigned char rD = (registerByte & 0b11110000) >> 4;
      unsigned char rS = registerByte & 0b00001111;
      short* operandDest = nullptr;
      bool isValid = true;
      short operand = getOperand(addressMode,upMode,rD,rS,&isValid,&operandDest);
      if(!isValid || operandDest == nullptr){
        this->registers[PC_REG] += 3;
        return;
      }
      *operandDest = this->registers[rD];

    }
    void Emulator::xchgInstruction(){
      unsigned char registerByte = memory[(SYSTEM_REGISTER)(this->registers[PC_REG]) + 1];
      unsigned char rD = (registerByte & 0b11110000) >> 4;
      unsigned char rS = registerByte & 0b00001111;
      if(rD >= 0b1000 || rS >=0b1000){
        return;
      }
      this->registers[PC_REG] +=2;
      unsigned short rDVal = this->registers[rD];
      unsigned short rSVal = this->registers[rS];
      unsigned short temp = rDVal;
      rDVal = rSVal;
      rSVal = temp;
      this->registers[rD] = rDVal;
      this->registers[rS] = rSVal;
     
    }
    void Emulator::addInstruction(){
      unsigned char registerByte = memory[(SYSTEM_REGISTER)(this->registers[PC_REG]) + 1];
      unsigned char rD = (registerByte & 0b11110000) >> 4;
      unsigned char rS = registerByte & 0b00001111;
      if(rD >= 0b1000 || rS >=0b1000){
        return;
      }
      this->registers[PC_REG] +=2;
      unsigned short rDVal = this->registers[rD];
      unsigned short rSVal = this->registers[rS];
      this->registers[rD] = rDVal + rSVal;
    }
    void Emulator::subInstruction(){
      unsigned char registerByte = memory[(SYSTEM_REGISTER)(this->registers[PC_REG]) + 1];
      unsigned char rD = (registerByte & 0b11110000) >> 4;
      unsigned char rS = registerByte & 0b00001111;
      if(rD >= 0b1000 || rS >=0b1000){
        return;
      }
      this->registers[PC_REG] +=2;
      unsigned short rDVal = this->registers[rD];
      unsigned short rSVal = this->registers[rS];
      this->registers[rD] = rDVal - rSVal;
    }
    void Emulator::mulInstruction(){
      unsigned char registerByte = memory[(SYSTEM_REGISTER)(this->registers[PC_REG]) + 1];
      unsigned char rD = (registerByte & 0b11110000) >> 4;
      unsigned char rS = registerByte & 0b00001111;
      if(rD >= 0b1000 || rS >=0b1000){
        return;
      }
      this->registers[PC_REG] +=2;
      unsigned short rDVal = this->registers[rD];
      unsigned short rSVal = this->registers[rS];
      this->registers[rD] = rDVal * rSVal;
    }
    void Emulator::divInstruction(){
      unsigned char registerByte = memory[(SYSTEM_REGISTER)(this->registers[PC_REG]) + 1];
      unsigned char rD = (registerByte & 0b11110000) >> 4;
      unsigned char rS = registerByte & 0b00001111;
      if(rD >= 0b1000 || rS >=0b1000){
        return;
      }
      this->registers[PC_REG] +=2;
      unsigned short rDVal = this->registers[rD];
      unsigned short rSVal = this->registers[rS];
      this->registers[rD] = rDVal / rSVal;
    }
    void Emulator::cmpInstruction(){}
    void Emulator::notInstruction(){}
    void Emulator::andInstruction(){}
    void Emulator::orInstruction(){}
    void Emulator::xorInstruction(){}
    void Emulator::testInstruction(){}
    void Emulator::shlInstruction(){}
    void Emulator::shrInstruction(){}


    short Emulator::getOperand(unsigned char adrMode,unsigned char upMod, unsigned char rD, unsigned char rS, bool* isValid,short** operandDest){
        ADDR_MODE addressMode = addressModes[adrMode];
        UP_MODE upMode = upModes[upMod];
        switch (addressMode)
        {
        case IMMED_ADR:
        {
          if(upMode!=NO_UPDATE || rS != 0b1111){
              *isValid = false;
              return -1;
          }
          unsigned char dataHigh = memory[(SYSTEM_REGISTER)(this->registers[PC_REG]) + 3];
          unsigned char dataLow = memory[(SYSTEM_REGISTER)(this->registers[PC_REG]) + 4];
          unsigned short operand = dataHigh;
          operand <<= 8;
          operand|=dataLow;
          this->registers[PC_REG] += 5;
          return operand;
        }
        case REGDIR_ADR:
        {
          if(rS >= 0b1000){
            *isValid = false;
            return -1;
          }
          switch (upMode)
          {
          case PRE_DEC:
            this->registers[rS]-=2;
            break;
          case PRE_INC:
            this->registers[rS]+=2;
            break;
          default:
            break;
          }
          this->registers[PC_REG] += 3;
          *operandDest = &this->registers[rS];
          short operand = this->registers[rS];
          switch (upMode)
          {
          case POST_DEC:
            this->registers[rS]-=2;
            break;
          case POST_INC:
            this->registers[rS]+=2;
            break;
          default:
            break;
          }
          return operand;

        }
        case REGDIR16_ADR:
        {
          if(rS >= 0b1000){
            *isValid = false;
            return -1;
          }
          switch (upMode)
          {
          case PRE_DEC:
            this->registers[rS]-=2;
            break;
          case PRE_INC:
            this->registers[rS]+=2;
            break;
          default:
            break;
          }
          unsigned char dataHigh = memory[(SYSTEM_REGISTER)(this->registers[PC_REG]) + 3];
          unsigned char dataLow = memory[(SYSTEM_REGISTER)(this->registers[PC_REG]) + 4];
          short addend = dataHigh;
          addend <<= 8;
          addend|=dataLow;
          this->registers[PC_REG] += 5;
          short operand = addend + this->registers[rS];
          
          switch (upMode)
          {
          case POST_DEC:
            this->registers[rS]-=2;
            break;
          case POST_INC:
            this->registers[rS]+=2;
            break;
          default:
            break;
          }
          return operand;
        }
        case REGIND_ADR:
        {
          if(rS >= 0b1000){
            *isValid = false;
            return -1;
          }
          switch (upMode)
          {
          case PRE_DEC:
            this->registers[rS]-=2;
            break;
          case PRE_INC:
            this->registers[rS]+=2;
            break;
          default:
            break;
          }
          this->registers[PC_REG] += 3;
          *operandDest = (short*)(memory[this->registers[rS]]);
          short operand = *((short*)(memory + this->registers[rS]));
          switch (upMode)
          {
          case POST_DEC:
            this->registers[rS]-=2;
            break;
          case POST_INC:
            this->registers[rS]+=2;
            break;
          default:
            break;
          }
          return operand;
        }
        case REGIND16_ADR: 
        {
          if(rS >= 0b1000){
            *isValid = false;
            return -1;
          }
          switch (upMode)
          {
          case PRE_DEC:
            this->registers[rS]-=2;
            break;
          case PRE_INC:
            this->registers[rS]+=2;
            break;
          default:
            break;
          }
          unsigned char dataHigh = memory[(SYSTEM_REGISTER)(this->registers[PC_REG]) + 3];
          unsigned char dataLow = memory[(SYSTEM_REGISTER)(this->registers[PC_REG]) + 4];
          short addend = dataHigh;
          addend <<= 8;
          addend|=dataLow;
          this->registers[PC_REG] += 5;
          short operand =*((short*)(memory + addend + this->registers[rS]));
          *operandDest = (short*)memory[addend + this->registers[rS]];
          
          switch (upMode)
          {
          case POST_DEC:
            this->registers[rS]-=2;
            break;
          case POST_INC:
            this->registers[rS]+=2;
            break;
          default:
            break;
          }
          return operand;
        }
        case MEM_ADR:
        {
          if(upMode!=NO_UPDATE || rS != 0b1111){
              *isValid = false;
              return -1;
          }
          unsigned char dataHigh = memory[(SYSTEM_REGISTER)(this->registers[PC_REG]) + 3];
          unsigned char dataLow = memory[(SYSTEM_REGISTER)(this->registers[PC_REG]) + 4];
          unsigned short operand = dataHigh;
          operand <<= 8;
          operand|=dataLow;
          this->registers[PC_REG] += 5;
          *operandDest = (short*)memory[operand];
          return *((short*)(memory + operand));
        }
        default:
          break;
        }
        *isValid = false;
        return 1;
    }