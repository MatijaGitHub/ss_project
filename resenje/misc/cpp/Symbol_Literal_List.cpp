#include "../hpp/Symbol_Literal_List.hpp"


  Symbol_Literal_List::Symbol_Literal_List(){
    this->symbols_and_literals = new std::vector<Symbol_Literal_Element*>();
  }
  void Symbol_Literal_List::pushSymbol(std::string* sym){
    this->symbols_and_literals->push_back(new Symbol_Literal_Element(true,sym,nullptr));  
  }
  void Symbol_Literal_List::pushLiteral(int lit){
    int* litP = new int(lit);
    *litP = lit;
    this->symbols_and_literals->push_back(new Symbol_Literal_Element(false,nullptr,litP));
  }

  Symbol_Literal_Element* Symbol_Literal_List::popLiteralSymbol(){
    if(!this->symbols_and_literals->empty()){
      Symbol_Literal_Element* retVal = this->symbols_and_literals->front();
      this->symbols_and_literals->erase(this->symbols_and_literals->begin());
      return retVal;
    }
    return nullptr;
  }
 
