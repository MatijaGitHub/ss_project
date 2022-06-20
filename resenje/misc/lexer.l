%{
  #include "parser.hpp"
  #include <stdio.h>
  #include <string>
  #include <stdlib.h>
 


  #define WRITE_SYMBOL yylval.symbol = new std::string(yytext,yyleng)
  #define WRITE_DECNUM yylval.number = std::atoi(yytext+1)
  #define WRITE_HEXNUM yylval.number = strtol(yytext+1,nullptr,16)
  #define WRITE_REGISTER yylval.reg = std::atoi(yytext+1)
  #define WRITE_SP yylval.reg = 6
  #define WRITE_PC yylval.reg = 7
  #define WRITE_PSW yylval.reg = 8
%}

%option outfile="./resenje/misc/FlexAndBison/lexer.cpp" header-file="./resenje/misc/FlexAndBison/lexer.hpp"
%option noyywrap


%%

".global"   {return GLOBAL;}
".extern"   {return EXTERN;}
".section"  {return SECTION;}
".word"     {return WORD;}
".skip"     {return SKIP;}
".ascii"    {return ASCII;}
".equ"      {return EQU;}
".end"      {return END;}
"halt"      {return HALT;}
"int"       {return INT;}
"iret"      {return IRET;}
"call"      {return CALL;}
"ret"       {return RET;}
"jmp"       {return JMP;}
"jeq"       {return JEQ;}
"jne"       {return JNE;}
"jgt"       {return JGT;}
"push"      {return PUSH;}
"pop"       {return POP;}
"xchg"      {return XCHG;}
"add"       {return ADD;}
"sub"       {return SUB;}
"mul"       {return MUL;}
"div"       {return DIV;}
"cmp"       {return CMP;}
"not"       {return NOT;}
"and"       {return AND;}
"or"        {return OR;}
"xor"       {return XOR;}
"test"      {return TEST;}
"shl"       {return SHL;}
"shr"       {return SHR;}
"ldr"       {return LDR;}
"str"       {return STR;}
"+"         {return PLUS;}
#.*         {return COMMENT;}
"sp"        {WRITE_SP; return REGISTER;}
"pc"        {WRITE_PC; return REGISTER;}
"psw"       {WRITE_PSW; return REGISTER;}
r[0-7]      {WRITE_REGISTER; return REGISTER;}
[a-zA-Z_][a-zA-Z0-9_]* {WRITE_SYMBOL; return SYMBOL;}
0x[0-9A-Fa-f]+        {WRITE_HEXNUM; return NUMBER;}
[0-9]+ WRITE_DECNUM; {return NUMBER;}
"%"         {return PERCENT;}
"*"         {return STAR;}
"$"         {return DOLLAR;}
"["         {return LEFT_BR;}
"]"         {return RIGHT_BR;}
":"         {return COLON;}
";"         {return SEMI_COLON;}
","         {return COMMA;}
"."         {return DOT;}
"\n"        {return NEW_LINE;}
[ \t]+      {;}




%%



