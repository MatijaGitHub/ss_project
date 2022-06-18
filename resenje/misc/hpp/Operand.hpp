#include <string>

class Operand{
  public:
  Operand(short* r);
  Operand(int* l);
  Operand(std::string*s);
  Operand(short* r, int *l);
  Operand(short *r, std::string*s);

  private:
      short* reg;
      int* literal;
      std::string* symbol;

};