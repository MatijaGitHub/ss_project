#pragma once
#include <vector>
#include <string>
#include "./Symbol_Literal_Element.hpp"


class Symbol_Literal_List{

  public:
  Symbol_Literal_List();
  void pushSymbol(std::string* sym);
  void pushLiteral(int lit);
  Symbol_Literal_Element* popLiteralSymbol();

  private:
  std::vector<Symbol_Literal_Element*> *symbols_and_literals;
};