#include "../hpp/Directive.hpp"


int Directive::getLiteral(){
  return this->literal;
}
DirectiveName Directive::getDirectiveName(){
  return this->dir;
}

Directive::Directive(DirectiveName dirID){
  this->dir = dirID;
}

Directive::Directive(DirectiveName dirID, int lit){
  this->dir = dirID;
  this->literal = lit;
}
Directive::Directive(DirectiveName dirID,Symbol_Literal_List list){
    this->dir = dirID;
    this->sym_lit_list = list;
}
Directive::Directive(DirectiveName dirID,std::string name){
  this->dir = dirID;
  this->stringUse = name;
}
Directive::Directive(DirectiveName dirID,std::vector<int> sym_ls){
  this->dir = dirID;
  this->symbolList = sym_ls;
}
std::string Directive::getString(){
  return this->stringUse;
}

std::string Directive::getDirNameString(){
  switch (this->dir)
  {
  case 0:
    return "global";
  case 1:
    return "extern";
  case 2:
    return "section";
  case 3:
    return "word";
  case 4:
    return "skip";
  case 5:
    return "ascii";
  case 6:
    return "equ";
  case 7:
    return "end";

  default:
    return "undefined";
    
  }
}