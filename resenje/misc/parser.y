%{
  #include <stdio.h>
  #include "helper.h"
	int yylex(void);
	void yyerror(const char*);
%}

%output "parser.c"
%defines "parser.h"

%union {
	int  number;
	char *symbol;
  char *string;
	
}
%token<number> TOKEN_LIT          
%token<symbol> TOKEN_SYMBOL
%token TOKEN_LPAR 
%token TOKEN_RPAR
%token TOKEN_PLUS
%token TOKEN_MINUS
%token TOKEN_SEMI
%token TOKEN_COMMA
%token TOKEN_DOT
%token TOKEN_MUL
%token TOKEN_DIV
%token TOKEN_COLON
%token TOKEN_NEWL
%token TOKEN_DOLLAR
%token TOKEN_PERCENT
%token<string> TOKEN_STRING

%type <symbol> rname;
%type <symbol> opCode;
%type <symbol> directive;
%type <symbol> label;


%%
translation
  :
  | line translation
  ;

label
  :
  TOKEN_SYMBOL TOKEN_COLON
  {$$ = $1;}
  ;

directive
  :
  TOKEN_DOT TOKEN_SYMBOL
  {if(!isDirective($2)){
        fprintf(stderr,"Bad directive name: %s",$2);
        return;
    }
      $$ = $2;}
  ;

instruction
  :
    opCode  
  | opCode rname  
  | opCode operandJump 
  | opCode rname TOKEN_COMMA operandValue 
  | opCode rname TOKEN_COMMA rname 
  ;
line
  :
      label
      {
        handleLabel($1);
      } 
    | label instruction
      {
        
      } 
    | label directive 
    | instruction 
    | directive
  ;
opCode
  :
    TOKEN_SYMBOL
    {if(!isOpcode($1)){
        fprintf(stderr,"Bad opcode name: %s",$1);
        return;
    }
      $$ = $1;}
  ;
operandValue
  :
    TOKEN_DOLLAR TOKEN_LIT
  | TOKEN_DOLLAR TOKEN_SYMBOL
  | TOKEN_LIT
  | TOKEN_SYMBOL
  | TOKEN_PERCENT TOKEN_SYMBOL
  | rname
  | TOKEN_LPAR rname TOKEN_RPAR
  | TOKEN_LPAR rname TOKEN_PLUS TOKEN_LIT TOKEN_RPAR
  | TOKEN_LPAR rname TOKEN_PLUS TOKEN_SYMBOL TOKEN_RPAR

  ;
operandJump
  :
      TOKEN_LIT
    | TOKEN_SYMBOL
    | TOKEN_PERCENT TOKEN_SYMBOL
    | TOKEN_MUL TOKEN_LIT
    | TOKEN_MUL TOKEN_SYMBOL
    | TOKEN_MUL rname
    | TOKEN_MUL TOKEN_LPAR rname TOKEN_RPAR
    | TOKEN_MUL TOKEN_LPAR rname TOKEN_PLUS TOKEN_LIT TOKEN_RPAR
    | TOKEN_MUL TOKEN_LPAR rname TOKEN_PLUS TOKEN_SYMBOL TOKEN_RPAR
  ;
rname
  : 
	TOKEN_SYMBOL
    {if(!isRegister($1)){
        fprintf(stderr,"Bad register name: %s",$1);
        return;
    }
      $$ = $1;}
  ;

%%