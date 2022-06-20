#include "../src/hpp/Assembler.hpp"
#include <vector>
#include <string>
#include <iostream>
#include <fstream>



int main()
{
  Assembler * as = new Assembler("test.s");
  as->assemble();
  
  return 0;
}