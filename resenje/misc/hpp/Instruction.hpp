#pragma once
#include "./Operand.hpp"

enum InstructionName{
  halt,intI,iret,call,ret,jmp,jeq,jne,jgt,push,pop,xchg,add,sub,mul,divI,cmp,notI,orI,andI,xorI,test,shl,shr,
  ldr,str
};


class Instruction{
  public:
  Instruction(InstructionName name);
  Instruction(InstructionName name, short reg1);
  Instruction(InstructionName name, short reg1, short reg2);
  Instruction(InstructionName name, Operand op);
  Instruction(InstructionName name, short reg1, Operand op);
  Operand getOperand();

  private:
  InstructionName name;
  short reg1;
  short reg2;
  Operand operand;

};