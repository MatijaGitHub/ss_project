#pragma once
#include "./Symbol_Literal_List.hpp"
#include <string>

enum DirectiveName{
  global,externI,section,word,skip,ascii,equ,end
};
class Directive{
public:
  Directive(DirectiveName dirID);
  Directive(DirectiveName dirID,int lit);
  Directive(DirectiveName dirID,Symbol_Literal_List list);
  Directive(DirectiveName dirID,std::string name);
  Directive(DirectiveName dirID,std::vector<int> sym_ls);
  void putSymbol(std::string symbol);
  DirectiveName getDirectiveName();
  int getLiteral();
  std::string getString();
  std::string getDirNameString();

private:
  DirectiveName dir;
  std::vector<int> symbolList;
  Symbol_Literal_List sym_lit_list;
  std::string stringUse;
  int literal;
};