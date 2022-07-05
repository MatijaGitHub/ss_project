#pragma once
#include "./Operand.hpp"
#include <vector>

class Expression{
  public:
  Expression();
  void pushOperand(Operand* op,int operation);
  std::pair<Operand*,int> getNext();
  private:
  std::vector<std::pair<Operand*,int>> expressionList;
};