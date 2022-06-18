#include <vector>
#include <string>


class Symbol_Literal_List{

  public:
  Symbol_Literal_List();
  void pushSymbol(std::string* sym);
  void pushLiteral(int lit);
  private:
  std::vector<std::string*> symbols;
  std::vector<int> literals;
};