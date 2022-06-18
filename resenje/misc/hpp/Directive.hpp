#include <string>
#include <vector>
#include "./Symbol_Literal_List.hpp"
enum DirectiveName{
  GLOBAL,EXTERN,SECTION,WORD,SKIP,ASCII,EQU,END
};
class Directive{
public:
  Directive(DirectiveName dirID);
  Directive(DirectiveName dirID,int lit);
  Directive(DirectiveName dirID,Symbol_Literal_List list);
  Directive(DirectiveName dirID,std::string name);
  Directive(DirectiveName dirID,std::vector<int> sym_ls);
  

protected:
  void putSymbol(std::string symbol);
  int getDirective();
  std::string getLiteral();

private:
  DirectiveName dir;
  std::vector<int> symbolList;
  Symbol_Literal_List sym_lit_list;
  std::string stringUse;
  int literal;
};