#include "../hpp/Symbol_Literal_List.hpp"


  Symbol_Literal_List::Symbol_Literal_List(){
    this->literals = new std::vector<int>();
    this->symbols  = new std::vector<std::string*>();
  }
  void Symbol_Literal_List::pushSymbol(std::string* sym){
    this->symbols->push_back(sym);
  }
  void Symbol_Literal_List::pushLiteral(int lit){
    this->literals->push_back(lit);
  }