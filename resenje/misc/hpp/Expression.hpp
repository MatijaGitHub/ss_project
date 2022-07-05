#pragma once
#include "./Operand.hpp"
#include <vector>

class Expression{
  public:
  Expression();
  void printExpression();
  void pushOperand(Operand* op,int operation);
  std::pair<Operand*,int> getNext();
  int getSize();
  std::vector<std::pair<Operand*,int>> getExpression();
  private:
  std::vector<std::pair<Operand*,int>> expressionList;
};