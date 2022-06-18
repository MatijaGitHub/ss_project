#include "./Operand.hpp"
#include <string>
enum JumpOperandType{
  LIT_VAL,ABS_SYM,REL_SYM,LIT_MEM,SYM_MEM,REG_VAL,REG_MEM,REG_LIT,REG_SYM
};

class JumpOperand : public Operand{
public:
  JumpOperand(JumpOperandType t,short *r);
  JumpOperand(JumpOperandType t,int *l);
  JumpOperand(JumpOperandType t,std::string *s);
  JumpOperand(JumpOperandType t,short *r, int *l);
  JumpOperand(JumpOperandType t,short *r, std::string *s);
private:
JumpOperandType type;
};