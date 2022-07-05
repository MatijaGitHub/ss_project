#include "../hpp/TNSTable.hpp"


TNSTable::TNSTable(){
  head = nullptr;
  tail = nullptr;
}
void TNSTable::addToTNS(std::string sym,Expression* exp){
  TNS* tns = new TNS();
  tns->nextTNS = nullptr;
  tns->exp = exp;
  tns->symbol = sym;
  if(head == nullptr){
    head = tns;
    tail = tns;
    return;
  }
  tail->nextTNS = tns;
  tail = tail->nextTNS;
}

void TNSTable::printTNS(){
  TNS* tmp = head;
  while (tmp!=nullptr)
  {
    printf("TNS_ENTRY %s = ",tmp->symbol.c_str());
    tmp->exp->printExpression();
    tmp = tmp->nextTNS;
  }
  
}