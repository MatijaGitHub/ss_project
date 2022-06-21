  #include "../hpp/Instruction.hpp"
  
  Instruction::Instruction(InstructionName name){
    this->name = name;
    this->operand = Operand();
    
  }
  Instruction::Instruction(InstructionName name, short reg1){
    this->name = name;
    this->reg1 = reg1;
    this->reg2 = -1;
    this->operand = Operand();
   
  }
  Instruction::Instruction(InstructionName name, short reg1, short reg2){
    this->name = name;
    this->reg1 = reg1;
    this->reg2 = reg2;
    this->operand = Operand();
 
  }
  Instruction::Instruction(InstructionName name, Operand op){
    this->name = name;
    this->operand = op;
    this->reg1 = -1;
    this->reg2 = -1;
  }
  Instruction::Instruction(InstructionName name, short reg1, Operand op){
    this->name = name;
    this->reg1 = reg1;
    this->reg2 = -1;
    this->operand = op;
  }

  Operand Instruction::getOperand(){
    return this->operand;
  }

  short Instruction::getDestReg(){
    return this->reg1;
  }
  short Instruction::getSourceReg(){
    return this->reg2;
  }
  int Instruction::getAdressTypeLength(){
      if(this->operand.needsPayload()){
        return 5;
      }
      return 3;
  }
  bool Instruction::isJumpIns(){
    if(this->name == jeq || this->name == call || this->name == jgt ||
        this->name == jmp || this->name == jne){
          return true;
    }
    return false;
  }
  AddressMode Instruction::getAddressMode(){
    OperandType op = this->operand.getType();
    if(op == LIT_VALUE || op == SYM_MEMORY){
      return immed;
    }
    else if(op == LIT_MEMORY || op == SYM_MEMORY){
      return memory;
    }
    else if(op == REG_VALUE){
      return regdir;
    }
    else if(op == SYM_RELATIVE && isJumpIns()){
      return regdirpom;
    }
    else if(op == REG_MEMORY){
      return regind;
    }
    else if((op == SYM_RELATIVE && !isJumpIns()) || op == REG_SYMBOL || op == REG_LITERAL){
      return regindpom;
    }
    else{
      return no_adr;
    }
  }
  int Instruction::getInstructionLength(){
    switch (this->name)
        {
        case 0:
          return 1;
        case 1:
          return 2;
        case 2:
          return 1;
        case 3:
          return getAdressTypeLength();
        case 4:
          return 1;
        case 5:
          return getAdressTypeLength();
        case 6:
          return getAdressTypeLength();
        case 7:
          return getAdressTypeLength();
        case 8:
          return getAdressTypeLength();
        case 9:
          return getAdressTypeLength();
        case 10:
          return getAdressTypeLength();
        case 11:
          return 2;
        case 12:
          return 2;
        case 13:
          return 2;
        case 14:
          return 2;
        case 15:
          return 2;
        case 16:
          return 2;
        case 17:
          return 2;
        case 18:
          return 2;
        case 19:
          return 2;
        case 20:
          return 2;                                                   
        case 21:
          return 2;
        case 22:
          return 2;
        case 23:
          return 2;
        case 24:
          return getAdressTypeLength();
        case 25:
          return getAdressTypeLength();
        default:
          return 0;
        }
  }
  std::string Instruction::getInstrNameString(){
    switch (this->name)
    {
    case 0:
      return "halt";
    case 1:
      return "int";
    case 2:
      return "iret";
    case 3:
      return "call";
    case 4:
      return "ret";
    case 5:
      return "jmp";
    case 6:
      return "jeq";
    case 7:
      return "jne";
    case 8:
      return "jgt";
    case 9:
      return "push";
    case 10:
      return "pop";
    case 11:
      return "xchg";
    case 12:
      return "add";
    case 13:
      return "sub";
    case 14:
      return "mul";
    case 15:
      return "div";
    case 16:
      return "cmp";
    case 17:
      return "not";
    case 18:
      return "or";
    case 19:
      return "and";
    case 20:
      return "xor";                                                   
    case 21:
      return "test";
    case 22:
      return "shl";
    case 23:
      return "shr";
    case 24:
      return "ldr";
    case 25:
      return "str";
    default:
      return "undfInstr";
    }
  }
  std::string Instruction::generateByteOfInstructions(int i){
      switch (i)
      {
      case 0:
        return this->generateFirstByte();
      case 1:
        return this->generateSecondByte();
      case 2:
        return this->generateThirdByte();
      case 3:
        return this->generateFourthByte();
      case 4:
        return this->generateFifthByte();
      default:
        return "";
      }
  }
  int Instruction::getOpCode(){
      switch (this->name)
      {
        case 0:
          return 0;
        case 1:
          return 16;
        case 2:
          return 32;
        case 3:
          return 48;
        case 4:
          return 64;
        case 5:
          return 80;
        case 6:
          return 81;
        case 7:
          return 82;
        case 8:
          return 83;
        case 9:
          return 176;
        case 10:
          return 160;
        case 11:
          return 96;
        case 12:
          return 112;
        case 13:
          return 113;
        case 14:
          return 114;
        case 15:
          return 115;
        case 16:
          return 116;
        case 17:
          return 128;
        case 18:
          return 130;
        case 19:
          return 129;
        case 20:
          return 131;                                                   
        case 21:
          return 132;
        case 22:
          return 144;
        case 23:
          return 145;
        case 24:
          return 160;
        case 25:
          return 176;
        default:
          return -1;
      }
      
  }
  std::string Instruction::generateFirstByte(){
    int opCode = this->getOpCode();
    std::stringstream stream;
    stream << std::setfill ('0') << std::setw(sizeof(short)) 
         << std::hex << opCode;
    return stream.str();
  }
  std::string Instruction::generateSecondByte(){
    short regDest = this->reg1!=-1?this->reg1:15;
    short regSource = this->reg2!=-1?this->reg2:15;
    int secondByte = (regDest << 4)|regSource;
    std::stringstream stream;
    stream << std::setfill ('0') << std::setw(sizeof(short)) 
         << std::hex << secondByte;
    return stream.str();
  }
  std::string Instruction::generateThirdByte(){
    return "";
  }
  std::string Instruction::generateFourthByte(){
    return "";
  }
  std::string Instruction::generateFifthByte(){
    return "";
  }