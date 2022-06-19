#pragma once
#include <string>

class Operand{
  public:
  Operand();
  Operand(short r);
  Operand(int l);
  Operand(std::string s);
  Operand(short r, int l);
  Operand(short r, std::string s);
  std::string getSymbol();

  private:
      short reg;
      int literal;
      std::string symbol;

};