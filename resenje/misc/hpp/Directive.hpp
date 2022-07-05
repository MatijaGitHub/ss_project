#pragma once
#include "./Symbol_Literal_List.hpp"
#include <string>

enum DirectiveName{
  global,externI,section,word,skip,ascii,equ,end
};
class Expression;
class Directive{
public:
  Directive(DirectiveName dirID);
  Directive(DirectiveName dirID,int lit);
  Directive(DirectiveName dirID,Symbol_Literal_List *list);
  Directive(DirectiveName dirID,std::string name);
  Directive(DirectiveName dirID,Expression* expression);
  void putSymbol(std::string symbol);
  DirectiveName getDirectiveName();
  int getLiteral();
  std::string getString();
  std::string getDirNameString();
  Symbol_Literal_List *getSymLitList();
  Expression* getExp();

private:
  DirectiveName dir;
  Symbol_Literal_List *sym_lit_list;
  Expression* expression;
  std::string stringUse;
  int literal;
};