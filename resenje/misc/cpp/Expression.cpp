#include "../hpp/Expression.hpp"



Expression::Expression(){
  
}

void Expression::pushOperand(Operand* op,int operation){
  std::pair<Operand*,int> operand;
  operand.first = op;
  operand.second = operation;
  this->expressionList.push_back(operand);
}
std::vector<std::pair<Operand*,int>> Expression::getExpression(){
  return this->expressionList;
}

 void Expression::printExpression(){
    int pos = 0;
    while(pos < this->expressionList.size()){
      if(expressionList.at(pos).second == 0){
        printf("- ");
      }
      else if(expressionList.at(pos).second == 1){
        printf("+ ");
      }
      if(expressionList.at(pos).first->isSymbol()){
          printf("%s ",expressionList.at(pos).first->getSymbol().c_str());
      }
      else{
          printf("%d ",expressionList.at(pos).first->getLiteral());
      }
      
      pos++;
    }
    printf("\n");
 }