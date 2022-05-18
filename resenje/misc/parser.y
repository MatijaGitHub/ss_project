%{
  #include <stdio.h>
  #include <stdlib.h>
  #include "helper.h"
	int yylex(void);
	void yyerror(const char*);
  FILE* yyin;
%}

%output "parser.c"
%defines "parser.h"

%union {
	int  number;
	char *symbol;
  char *string;
  instruction* instruction;
  operand* operand;
	
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

%type <symbol> opCode;
%type <symbol> directive;
%type <symbol> label;
%type <instruction> instruction;
/* %type <operand> operandValue; */
%type <operand> operandJump;
%type <symbol> rname;


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
      $$ = createInstruction($1,NULL,NULL,NULL);
    }  
  | opCode rname 
    {
      $$ = createInstruction($1,$2,NULL,NULL);
    }  
  | opCode operandJump 
    {
     $$ = createInstruction($1,NULL,NULL,$2);
    } 
  /* | opCode rname TOKEN_COMMA operandValue  
    {
      $$ = createInstruction($1,$2,NULL,$4);
    }  */
  | opCode rname TOKEN_COMMA rname 
    {
      $$ = createInstruction($1,$2,$4,NULL);
    } 
  ;
line
  :
      label 
      {
        addLine(createLine($1,NULL,NULL));
      } 
    | label instruction 
      {
        addLine(createLine($1,NULL,$2));
      } 
    | label directive 
      {
        addLine(createLine($1,$2,NULL));
      }
    | instruction 
      {
        addLine(createLine(NULL,NULL,$1));
      }
    | directive 
      {
        addLine(createLine(NULL,$1,NULL));
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
/* operandValue
  :
    TOKEN_DOLLAR TOKEN_LIT 
    {
      $$ = createOperand(1,0,9,$2,NULL,NULL);
    }
  | TOKEN_DOLLAR TOKEN_SYMBOL 
    {
      $$ = createOperand(1,1,9,NULL,NULL,$2);
    }
  | TOKEN_LIT 
    {
      $$ = createOperand(1,2,9,$1,NULL,NULL);
    }
  | TOKEN_SYMBOL 
    {
      $$ = createOperand(1,3,9,NULL,NULL,$1);
    }
  | TOKEN_PERCENT TOKEN_SYMBOL 
    {
      $$ = createOperand(1,4,9,NULL,NULL,$2);
    }
  | rname TOKEN_DIV
    {
      $$ = createOperand(1,5,9,NULL,$1,NULL);
    }
  | TOKEN_LPAR rname TOKEN_RPAR 
    {
      $$ = createOperand(1,6,9,NULL,$2,NULL);
    }
  | TOKEN_LPAR rname TOKEN_PLUS TOKEN_LIT TOKEN_RPAR 
    {
      $$ = createOperand(1,7,9,$4,$2,NULL);
    }
  | TOKEN_LPAR rname TOKEN_PLUS TOKEN_SYMBOL TOKEN_RPAR 
    {
      $$ = createOperand(1,8,9,NULL,$2,$4);
    }

  ; */
operandJump
  :
      TOKEN_LIT 
      {
        $$ = createOperand(0,9,0,$1,NULL,NULL);
      }
    | TOKEN_SYMBOL TOKEN_NEWL
      {
        $$ = createOperand(0,9,1,NULL,NULL,$1);
      }
    | TOKEN_PERCENT TOKEN_SYMBOL TOKEN_NEWL
      {
        $$ = createOperand(0,9,2,NULL,NULL,$2);
      }
    | TOKEN_MUL TOKEN_LIT TOKEN_NEWL
      {
        $$ = createOperand(0,9,3,$2,NULL,NULL);
      }
    | TOKEN_MUL TOKEN_SYMBOL TOKEN_NEWL
      {
        $$ = createOperand(0,9,4,NULL,NULL,$2);
      }
    | TOKEN_MUL rname 
      {
        $$ = createOperand(0,9,5,NULL,$2,NULL);
      }
    | TOKEN_MUL TOKEN_LPAR rname TOKEN_RPAR 
      {
        $$ = createOperand(0,9,6,NULL,$3,NULL);
      }
    | TOKEN_MUL TOKEN_LPAR rname TOKEN_PLUS TOKEN_LIT TOKEN_RPAR 
      {
        $$ = createOperand(0,9,7,$5,$3,NULL);
      }
    | TOKEN_MUL TOKEN_LPAR rname TOKEN_PLUS TOKEN_SYMBOL TOKEN_RPAR 
      {
        $$ = createOperand(0,9,8,NULL,$3,$5);
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

int parser_main(){
   FILE* fp = NULL;
   fp = fopen("./test.txt","r");
   yyin = fp;
   yyparse();
   fclose(fp);
   return 0;

}
