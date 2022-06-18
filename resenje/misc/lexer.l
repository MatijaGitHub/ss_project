%{
  #include "parser.h"
  #include <stdio.h>
  #include <string>
 


  #define WRITE_SYMBOL yyval.symbol = std::string(yytext,yyleng)
  #define WRITE_DECNUM yyval.number = std::atoi(yytext+1)
  #define WRITE_HEXNUM yyval.number = std::strol(yytext+1,nullptr,16)
  #define WRITE_REGISTER yyval.reg = std::atoi(yytext+1)
  #define WRITE_SP yyval.reg = 6
  #define WRITE_PC yyval.reg = 7
  #define WRITE_PSW yyval.reg = 8
%}

%option outfile="lexer.c" header-file="lexer.h"
%option noyywrap

%%

".global"   return GLOBAL;
".extern"   return EXTERN;
".section"  return SECTION;
".word"     return WORD;
".skip"     return SKIP;
".ascii"    return ASCII;
".equ"      return EQU;
".end"      return END;
"halt"      return HALT;
"int"       return INT;
"iret"      return IRET;
"call"      return CALL;
"ret"       return RET;
"jmp"       return JMP;
"jeq"       return JEQ;
"jne"       return JNE;
"jgt"       return JGT;
"push"      return PUSH;
"pop"       return POP;
"xchg"      return XCHG;
"add"       return ADD;
"sub"       return SUB;
"mul"       return MUL;
"div"       return DIV;
"cmp"       return CMP;
"not"       return NOT;
"and"       return AND;
"or"        return OR;
"xor"       return XOR;
"test"      return TEST;
"shl"       return SHL;
"shr"       return SHR;
"ldr"       return LDR;
"str"       return STR;
"+"         return PLUS;
#.*         return COMMENT;
"sp"        WRITE_SP; return SP;
"pc"        WRITE_PC; return PC;
"psw"       WRITE_PSW; return PSW;
r[0-7]      WRITE_REGISTER; return REGISTER;
[a-zA-Z_][a-zA-Z0-9_]* WRITE_SYMBOL; return LITERAL;
0x[0-9A-Fa-f]+ WRITE_HEXNUM; return NUMBER;
[0-9]+ WRITE_DECNUM; return NUMBER;
"%"         return PERCENT;
"*"         return STAR;
"$"         return DOLLAR;
"["         return LEFT_BR;
"]"         return RIGHT_BR;
":"         return COLON;
";"         return SEMI_COLON;
","         return COMMA;
"\n"        return NEW_LINE;
[ \t]+      ;




%%




int
yyerror(const char* msg)
{
    fprintf(stderr, "lexer error: %s\n", msg);
    return 0;
}