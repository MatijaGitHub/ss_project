#include "helper.h"
#include "parser.h"
extern int parser_main();
extern void printLines();
extern void yyerror();

int main(int argc, char *argv[]) {
  parser_main();
  printLines();
  return 0;
}
