%{
  #include <stdio.h>
  #include <stdlib.h>



	extern int yylex(void);
	extern void yyerror(const char*);
  extern FILE* yyin;
  extern int yylineno;
  int yydebug = 1;
  extern char *yytext;

  void yyerror(const char *s) { 
      printf("Syntax error on line: %d\n", yylineno);
  }

%}
%code requires {

#include "../hpp/Lines.hpp"


}
%output "./resenje/misc/FlexAndBison/parser.cpp"
%defines "./resenje/misc/FlexAndBison/parser.hpp"

%union{
  Line *line;
  Symbol_Literal_List * sym_lit_list;
  //Symbol_Literal_List *list_of_symbols;
  std::string *symbol;
  Directive* dir;
  Instruction* ins;
  Label* lbl;
  Operand* operand;
  // JumpOperand* jmpOp;
  // DataOperand* dataOp;
  short reg;
  int number;
  int token;
}

%token<reg> REGISTER;
%token<symbol> SYMBOL STRING;
%token<number> NUMBER;
%token<token> GLOBAL EXTERN SECTION WORD SKIP ASCII EQU END;
%token<token> HALT INT IRET RET CALL JMP JGT JEQ JNE PUSH POP XCHG ADD SUB MUL DIV CMP NOT AND OR XOR;
%token<token> TEST SHL SHR LDR STR PLUS COMMENT PERCENT STAR DOLLAR LEFT_BR RIGHT_BR COLON SEMI_COLON;
%token<token> NEW_LINE;
%token<token> COMMA DOT;
%token<symbol> DIR;


%type<line> line;
%type<sym_lit_list> list_of_symbols;
%type<sym_lit_list> list_of_symbols_and_literals;
%type<dir> directive;
%type<ins> instruction;
%type<lbl> label;
%type<operand> operandData;
%type<operand> operandJump;
/* %type<dataOp> operandData;
%type<jmpOp> operandJump; */





%start code



%%
code:
  lines{
    //Lines::initLines();
  }
  ;
lines:
  line{
    if($1 != nullptr){
      
      Lines::writeLine($1);
      
      yylineno++;
    }
  }
  |
  lines line{
    if($2 != nullptr){
     
      Lines::writeLine($2);
      yylineno++;
    }
  }
  ;
line:
  NEW_LINE{
    $$ = nullptr;
  }
  |
  label NEW_LINE{
    $$ = new Line($1);
    
  }
  |
  label directive NEW_LINE{
    $$ = new Line($1,$2);
  }
  |
  label instruction NEW_LINE{
    $$ = new Line($1,$2);

  }
  | 
  instruction NEW_LINE{
    $$ = new Line($1);
  }
  |
  directive NEW_LINE{
    $$ = new Line($1);
  }
  |
  label COMMENT NEW_LINE{
    $$ = new Line($1);
  }
  |
  label directive COMMENT NEW_LINE{
    $$ = new Line($1,$2);
  }
  |
  label instruction COMMENT NEW_LINE{
    $$ = new Line($1,$2);
  }
  |
  COMMENT NEW_LINE{
    $$ = nullptr;
  }
  |
  instruction COMMENT NEW_LINE{
    $$ = new Line($1);
  }
  |
  directive COMMENT NEW_LINE{
    $$ = new Line($1);
  }
  ;


directive:
  GLOBAL list_of_symbols{
    $$ = new Directive(global,$2);
    
  }
  |
  EXTERN list_of_symbols{
    $$ = new Directive(externI,$2);
    
  }
  |
  SECTION DIR{
    $$ = new Directive(section,*$2);
  }
  |
  SECTION SYMBOL{
    $$ = new Directive(section,*$2);
  }
  |
  WORD list_of_symbols_and_literals{
    $$ = new Directive(word,$2);
    
  }
  |
  SKIP NUMBER{
    $$ = new Directive(skip,$2);
  }
  |
  ASCII STRING{
    $$ = new Directive(ascii,*$2);
  }
  |
  END{
    $$ = new Directive(end);
  }
  ;

instruction:
  HALT{
      $$ = new Instruction(InstructionName::halt);
  }
  |
  INT REGISTER{
       $$ = new Instruction(InstructionName::intI,$2);
  }
  |
  IRET{
    $$ = new Instruction(InstructionName::iret);
  }
  |
  CALL operandJump{
    $$ = new Instruction(InstructionName::call,*$2);
  }
  |
  RET{
    $$ = new Instruction(InstructionName::ret);
  }
  |
  JMP operandJump{
    $$ = new Instruction(InstructionName::jmp,*$2);
  }
  |
  JGT operandJump{
    $$ = new Instruction(InstructionName::jgt,*$2);
  }
  |
  JEQ operandJump{
    $$ = new Instruction(InstructionName::jeq,*$2);
  }
  |
  JNE operandJump{
    $$ = new Instruction(InstructionName::jne,*$2);
  }
  |
  PUSH REGISTER{
      $$ = new Instruction(InstructionName::push,$2);
  }
  |
  POP REGISTER{
      $$ = new Instruction(InstructionName::pop,$2);
  }
  |
  XCHG REGISTER COMMA  REGISTER{
      $$ = new Instruction(InstructionName::xchg,$2,$4);
  }
  |
  ADD REGISTER COMMA  REGISTER{
      $$ = new Instruction(InstructionName::add,$2,$4);
  }
  |
  SUB REGISTER COMMA REGISTER{
      $$ = new Instruction(InstructionName::sub,$2,$4);
  }
  |
  MUL REGISTER COMMA REGISTER{
      $$ = new Instruction(InstructionName::mul,$2,$4);
  }
  |
  DIV REGISTER COMMA REGISTER{
      $$ = new Instruction(InstructionName::divI,$2,$4);
  }
  |
  CMP REGISTER COMMA REGISTER{
      $$ = new Instruction(InstructionName::cmp,$2,$4);
  }
  |
  NOT REGISTER{
      $$ = new Instruction(InstructionName::notI,$2);
  }
  |
  AND REGISTER COMMA REGISTER{
      $$ = new Instruction(InstructionName::andI,$2,$4);
  }
  |
  OR REGISTER COMMA REGISTER{
      $$ = new Instruction(InstructionName::orI,$2,$4);
  }
  | 
  XOR REGISTER COMMA REGISTER{
      $$ = new Instruction(InstructionName::xorI,$2,$4);
  }
  |
  TEST REGISTER COMMA REGISTER{
      $$ = new Instruction(InstructionName::test,$2,$4);
  }
  |
  SHL REGISTER COMMA REGISTER{
      $$ = new Instruction(InstructionName::shl,$2,$4);
  }
  |
  SHR REGISTER COMMA REGISTER{
      $$ = new Instruction(InstructionName::shr,$2,$4);
  }
  |
  LDR REGISTER COMMA operandData{
      $$ = new Instruction(InstructionName::ldr,$2,*$4);
  }
  |
  STR REGISTER COMMA operandData{
      $$ = new Instruction(InstructionName::str,$2,*$4);
  }
  ;
operandData:
  DOLLAR NUMBER{
    $$ = new Operand(LIT_VALUE,$2);
  }
  |
  DOLLAR SYMBOL{
      $$ = new Operand(SYM_VALUE,*$2);
  }
  |
  NUMBER{
      $$ = new Operand(LIT_MEMORY,$1);
  }
  |
  SYMBOL{
      $$ = new Operand(SYM_MEMORY,*$1);
  }
  |
  PERCENT SYMBOL{
      $$ = new Operand(SYM_RELATIVE,*$2);
  }
  |
  REGISTER{
      $$ = new Operand(REG_VALUE,$1);
  }
  |
  LEFT_BR REGISTER RIGHT_BR{
      $$ = new Operand(REG_MEMORY,$2);
  }
  |
  LEFT_BR REGISTER PLUS NUMBER RIGHT_BR{
      $$ = new Operand(REG_LITERAL,$2,$4);
  }
  |
  LEFT_BR REGISTER PLUS SYMBOL RIGHT_BR{
      $$ = new Operand(REG_SYMBOL,$2,*$4);
  }
  ;

operandJump:
  NUMBER{
      $$ = new Operand(LIT_VALUE,$1);
  }
  |
  SYMBOL{
      $$ = new Operand(SYM_VALUE,*$1);
  }
  |
  PERCENT SYMBOL{
      $$ = new Operand(SYM_RELATIVE,*$2);
  }
  |
  STAR NUMBER{
      $$ = new Operand(LIT_MEMORY,$2);
  }
  |
  STAR SYMBOL{
      $$ = new Operand(SYM_MEMORY,*$2);
  }
  |
  STAR REGISTER{
      $$ = new Operand(REG_VALUE,$2);
  }
  |
  STAR LEFT_BR REGISTER RIGHT_BR{
      $$ = new Operand(REG_MEMORY,$3);
  }
  |
  STAR LEFT_BR REGISTER PLUS SYMBOL RIGHT_BR{
      $$ = new Operand(REG_SYMBOL,$3,*$5);
  }
  |
  STAR LEFT_BR REGISTER PLUS NUMBER RIGHT_BR{
      $$ = new Operand(REG_LITERAL,$3,$5);
  }
  ;

label:
  SYMBOL COLON{
    $$ = new Label(*$1);
  }
  ;

list_of_symbols:
  SYMBOL{
      $$ = new Symbol_Literal_List();
      $$->pushSymbol($1);
      
  }
  |
  list_of_symbols COMMA SYMBOL{
      $$->pushSymbol($3);
      
  }
  ;
list_of_symbols_and_literals:
  SYMBOL{
    $$ = new Symbol_Literal_List();
    $$->pushSymbol($1);
  }
  |
  NUMBER{
    $$ = new Symbol_Literal_List();
    $$->pushLiteral($1);
  }
  |
  list_of_symbols_and_literals COMMA SYMBOL{
      $$->pushSymbol($3);
  }
  |
  list_of_symbols_and_literals COMMA NUMBER{
      $$->pushLiteral($3);
  }
  ;
  


%%