#include "../hpp/Symbol_Literal_Element.hpp"



Symbol_Literal_Element::Symbol_Literal_Element(bool isS,std::string* sym,int* lit){
  this->isSymbol = isS;
  this->symbol = sym;
  this->literal = lit;
}
