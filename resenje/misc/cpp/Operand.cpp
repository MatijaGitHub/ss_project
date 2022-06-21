#include "../hpp/Operand.hpp"

  Operand::Operand(){
    this->type = NO_TYPE;
  }
  Operand::Operand(OperandType type,short r){
    this->type = type;
    this->reg = r;
  }
  Operand::Operand(OperandType type,int l){
    this->type = type;
    this->literal = l;
  }
  Operand::Operand(OperandType type,std::string s){
    this->type = type;
    this->symbol = s;
  }
  Operand::Operand(OperandType type,short r, int l){
    this->type = type;
    this->reg = r;
    this->literal = l;
  }
  Operand::Operand(OperandType type,short r, std::string s){
    this->type = type;
    this->reg = r;
    this->symbol = s;
  }
  std::string Operand::getSymbol(){
    return this->symbol;
  }

  OperandType Operand::getType(){
    return this->type;
  }

  bool Operand::needsPayload(){
    if(this->type == LIT_VALUE || this->type == SYM_VALUE || this->type == LIT_MEMORY ||
       this->type == SYM_MEMORY || this->type == SYM_RELATIVE || this->type == REG_LITERAL ||
       this->type == REG_SYMBOL){
        return true;
       }
       return false;
  }