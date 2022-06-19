
 #include "./hpp/Lines.hpp"

#include <vector>
#include <string>

int main()
{
  Operand op(std::string("SEKS"));
  Instruction *ins = new Instruction(call,op);
  Line *l = new Line(ins); 
  Lines::initLines();
  Lines::writeLine(l);
  Lines::readLines();
  return 0;

}