#include "../hpp/DataOperand.hpp"
  // DataOperand(DataOperandType t,std::string s);
  // DataOperand(DataOperandType t,short r, int l);
  // DataOperand(DataOperandType t,short r, std::string s);
  DataOperand::DataOperand(DataOperandType t, short *r)
  : Operand(r)
  {
    this->type = t;
  }
  DataOperand::DataOperand(DataOperandType t,int *l)
  : Operand(l)
  {
    this->type = t;
  }
  DataOperand::DataOperand(DataOperandType t,std::string* s)
  : Operand(s)
  {
    this->type = t;
  }