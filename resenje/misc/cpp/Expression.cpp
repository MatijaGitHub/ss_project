#include "../hpp/Expression.hpp"



Expression::Expression(){
  
}

void Expression::pushOperand(Operand* op,int operation){
  std::pair<Operand*,int> operand;
  operand.first = op;
  operand.second = operation;
  this->expressionList.push_back(operand);
}