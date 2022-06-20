#include "../hpp/Symbol_Literal_List.hpp"


  Symbol_Literal_List::Symbol_Literal_List(){
    this->literals = new std::vector<int*>();
    this->symbols  = new std::vector<std::string*>();
  }
  void Symbol_Literal_List::pushSymbol(std::string* sym){
    this->symbols->push_back(sym);
  }
  void Symbol_Literal_List::pushLiteral(int *lit){
    this->literals->push_back(lit);
  }
  std::string* Symbol_Literal_List::popSymbol(){
    if(!this->symbols->empty()){
      std::string * retVal = this->symbols->back();
      this->symbols->pop_back();
      return retVal;
    }
    return nullptr;
  }
  int* Symbol_Literal_List::popLiteral(){
    if(!this->literals->empty()){
      int* retVal = this->literals->back();
      this->literals->pop_back();
      return retVal;
    }
    return nullptr;
  }