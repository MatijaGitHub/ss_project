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