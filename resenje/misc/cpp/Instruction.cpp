  #include "../hpp/Instruction.hpp"
  
  Instruction::Instruction(InstructionName name){
    this->name = name;
    
  }
  Instruction::Instruction(InstructionName name, short reg1){
    this->name = name;
    this->reg1 = reg1;
   
  }
  Instruction::Instruction(InstructionName name, short reg1, short reg2){
    this->name = name;
    this->reg1 = reg1;
    this->reg2 = reg2;
 
  }
  Instruction::Instruction(InstructionName name, Operand op){
    this->name = name;
    this->operand = op;
  }
  Instruction::Instruction(InstructionName name, short reg1, Operand op){
    this->name = name;
    this->reg1 = reg1;
    this->operand = op;
  }

  Operand Instruction::getOperand(){
    return this->operand;
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