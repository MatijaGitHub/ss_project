#pragma once
#include <string>
enum OperandType{
  NO_TYPE,LIT_VALUE,SYM_VALUE,LIT_MEMORY,SYM_MEMORY,SYM_RELATIVE,REG_VALUE,REG_MEMORY,REG_LITERAL,REG_SYMBOL
};
class Operand{
  public:
  Operand();
  Operand(OperandType type);
  Operand(OperandType type,short r);
  Operand(OperandType type,int l);
  Operand(OperandType type,std::string s);
  Operand(OperandType type,short r, int l);
  Operand(OperandType type,short r, std::string s);
  std::string getSymbol();
  OperandType getType();
  bool needsPayload();
  bool isSymbol();
  short getRegister();
  int getLiteral();

  private:
      short reg;
      int literal;
      std::string symbol;
      OperandType type;

};