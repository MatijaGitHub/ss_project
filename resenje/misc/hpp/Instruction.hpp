#include "./Operand.hpp"

enum InstructionName{
  HALT,INT,IRET,CALL,RET,JMP,JEQ,JNE,JGT,PUSH,POP,XCHG,ADD,SUB,MUL,DIV,CMP,NOT,OR,AND,XOR,TEST,SHL,SHR,
  LDR,STR
};


class Instruction{
  public:
  Instruction(InstructionName name);
  Instruction(InstructionName name, short reg1);
  Instruction(InstructionName name, short reg1, short reg2);
  Instruction(InstructionName name, Operand op);
  Instruction(InstructionName name, short reg1, Operand op);

  private:
  InstructionName name;
  short reg1;
  short reg2;
  Operand operand;

};