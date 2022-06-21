#pragma once
#include "./Operand.hpp"
#include <iomanip>


enum InstructionName{
  halt,intI,iret,call,ret,jmp,jeq,jne,jgt,push,pop,xchg,add,sub,mul,divI,cmp,notI,orI,andI,xorI,test,shl,shr,
  ldr,str
};
enum AddressMode{
  no_adr,immed,regdir,regdirpom,regind,regindpom,memory
};

class Instruction{
  public:
  Instruction(InstructionName name);
  Instruction(InstructionName name, short reg1);
  Instruction(InstructionName name, short reg1, short reg2);
  Instruction(InstructionName name, Operand op);
  Instruction(InstructionName name, short reg1, Operand op);
  Operand getOperand();
  short getDestReg();
  short getSourceReg();
  std::string getInstrNameString();
  int getInstructionLength();
  int getAdressTypeLength();
  AddressMode getAddressMode();
  bool isJumpIns();
  std::string generateByteOfInstructions(int i,unsigned long symVal);
  std::string generateFirstByte();
  std::string generateSecondByte();
  std::string generateThirdByte();
  std::string generateFourthByte(unsigned long symVal);
  std::string generateFifthByte(unsigned long symVal);
  int getOpCode();

  

  private:
  InstructionName name;
  short reg1;
  short reg2;
  Operand operand;

};