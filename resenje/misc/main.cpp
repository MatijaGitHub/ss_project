#include "./hpp/Lines.hpp"
#include <vector>
#include <string>
#include <iostream>
#include <fstream>

extern int yyparse();
extern FILE* yyin;

int main()
{
  yyin = fopen("test.s","r");
  int ret = yyparse();
  Lines::readLines();
  return 0;
}