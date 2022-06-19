#include "../hpp/JumpOperand.hpp"
  JumpOperand::JumpOperand(JumpOperandType t, short r)
  : Operand(r)
  {
    this->type = t;
  }
  JumpOperand::JumpOperand(JumpOperandType t,int l)
  : Operand(l)
  {
    this->type = t;
  }
  JumpOperand::JumpOperand(JumpOperandType t,std::string s)
  : Operand(s)
  {
    this->type = t;
  }
  JumpOperand::JumpOperand(JumpOperandType t, short r, int l)
  : Operand(r,l)
  { 
    this->type = t;
  }
  JumpOperand::JumpOperand(JumpOperandType t, short r, std::string s)
  : Operand(r,s)
  {
    this->type = t;
  }