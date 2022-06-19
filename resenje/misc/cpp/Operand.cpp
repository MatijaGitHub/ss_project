#include "../hpp/Operand.hpp"

  Operand::Operand(){}
  Operand::Operand(short r){
    this->reg = r;
  }
  Operand::Operand(int l){
    this->literal = l;
  }
  Operand::Operand(std::string s){
    this->symbol = s;
  }
  Operand::Operand(short r, int l){
    this->reg = r;
    this->literal = l;
  }
  Operand::Operand(short r, std::string s){
    this->reg = r;
    this->symbol = s;
  }
  std::string Operand::getSymbol(){
    return this->symbol;
  }