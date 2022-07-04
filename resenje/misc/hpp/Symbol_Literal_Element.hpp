#pragma once
#include <string>


class Symbol_Literal_Element{
  public:
  Symbol_Literal_Element(bool isS,std::string* sym,int* lit);
  bool isSymbol;
  std::string* symbol;
  int* literal;
};

