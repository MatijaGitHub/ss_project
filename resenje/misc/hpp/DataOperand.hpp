#include "./Operand.hpp"
#include <string>
enum DataOperandType{
  LIT_VALUE,SYM_VALUE,LIT_MEMORY,SYM_MEMORY,SYM_RELATIVE,REG_VALUE,REG_MEMORY,REG_LITERAL,REG_SYMBOL
};

class DataOperand : public Operand{
public:
  DataOperand(DataOperandType t,short *r);
  DataOperand(DataOperandType t,int *l);
  DataOperand(DataOperandType t,std::string *s);
  DataOperand(DataOperandType t,short *r, int *l);
  DataOperand(DataOperandType t,short *r, std::string *s);
private:
DataOperandType type;
};