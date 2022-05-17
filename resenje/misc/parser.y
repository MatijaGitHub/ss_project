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
  instruction* instruction;
	
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
%type <instruction> instruction;


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
  {if(isDirective($2)==0){
        fprintf(stderr,"Bad directive name: %s",$2);
        return;
    }
      $$ = $2;}
  ;

instruction
  :
    opCode
    {
      $$ = createInstruction($1,nullptr,nullptr,nullptr);
    }  
  | opCode rname
    {
      $$ = createInstruction($1,$2,nullptr,nullptr);
    }  
  | opCode operandJump 
    {
      $$ = createInstruction($1,nullptr,nullptr,$2);
    } 
  | opCode rname TOKEN_COMMA operandValue 
    {
      $$ = createInstruction($1,$2,nullptr,$4);
    } 
  | opCode rname TOKEN_COMMA rname 
    {
      $$ = createInstruction($1,$2,$4,nullptr);
    } 
  ;
line
  :
      label
      {
        addLine(createLine($1,nullptr,nullptr));
      } 
    | label instruction
      {
        addLine(createLine($1,nullptr,$2));
      } 
    | label directive 
      {
        addLine(createLine($1,$2,nullptr));
      }
    | instruction 
      {
        addLine(createLine(nullptr,nullptr,$1));
      }
    | directive
      {
        addLine(createLine(nullptr,$1,nullptr));
      }
  ;
opCode
  :
    TOKEN_SYMBOL
    {if(isOpcode($1)==0){
        fprintf(stderr,"Bad opcode name: %s",$1);
        return;
    }
      $$ = $1;}
  ;
operandValue
  :
    TOKEN_DOLLAR TOKEN_LIT
    {
      createOperand(1,0,9,$2,nullptr,nullptr);
    }
  | TOKEN_DOLLAR TOKEN_SYMBOL
    {
      createOperand(1,1,9,nullptr,nullptr,$2);
    }
  | TOKEN_LIT
    {
      createOperand(1,2,9,$1,nullptr,nullptr);
    }
  | TOKEN_SYMBOL
    {
      createOperand(1,3,9,nullptr,nullptr,$1);
    }
  | TOKEN_PERCENT TOKEN_SYMBOL
    {
      createOperand(1,4,9,nullptr,nullptr,$2);
    }
  | rname
    {
      createOperand(1,5,9,nullptr,$1,nullptr);
    }
  | TOKEN_LPAR rname TOKEN_RPAR
    {
      createOperand(1,6,9,nullptr,$2,nullptr);
    }
  | TOKEN_LPAR rname TOKEN_PLUS TOKEN_LIT TOKEN_RPAR
    {
      createOperand(1,7,9,$4,$2,nullptr);
    }
  | TOKEN_LPAR rname TOKEN_PLUS TOKEN_SYMBOL TOKEN_RPAR
    {
      createOperand(1,8,9,nullptr,$2,$4);
    }

  ;
operandJump
  :
      TOKEN_LIT
      {
        createOperand(0,9,0,$1,nullptr,nullptr);
      }
    | TOKEN_SYMBOL
      {
        createOperand(0,9,1,nullptr,nullptr,$1);
      }
    | TOKEN_PERCENT TOKEN_SYMBOL
      {
        createOperand(0,9,2,nullptr,nullptr,$2);
      }
    | TOKEN_MUL TOKEN_LIT
      {
        createOperand(0,9,3,$2,nullptr,nullptr);
      }
    | TOKEN_MUL TOKEN_SYMBOL
      {
        createOperand(0,9,4,nullptr,nullptr,$2);
      }
    | TOKEN_MUL rname
      {
        createOperand(0,9,5,nullptr,$2,nullptr);
      }
    | TOKEN_MUL TOKEN_LPAR rname TOKEN_RPAR
      {
        createOperand(0,9,6,nullptr,$3,nullptr);
      }
    | TOKEN_MUL TOKEN_LPAR rname TOKEN_PLUS TOKEN_LIT TOKEN_RPAR
      {
        createOperand(0,9,7,$5,$3,nullptr);
      }
    | TOKEN_MUL TOKEN_LPAR rname TOKEN_PLUS TOKEN_SYMBOL TOKEN_RPAR
      {
        createOperand(0,9,8,nullptr,$3,$5);
      }
  ;
rname
  : 
	TOKEN_SYMBOL
    {if(isRegister($1)==0){
        fprintf(stderr,"Bad register name: %s",$1);
        return;
    }
      $$ = $1;}
  ;

%%