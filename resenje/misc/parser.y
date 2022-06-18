%{
  #include <stdio.h>
  #include <stdlib.h>
  #include "./h/Lines.hpp"
  #include "./h/Line.hpp"
  #include "./h/Symbol_Literal_List.hpp"
  #include "./h/Directive.hpp"
  #include "./h/Instruction.hpp"
  #include "./h/Label.hpp"
  #include "./h/DataOperand.hpp"
  #include "./h/JumpOperand.hpp"
	int yylex(void);
	void yyerror(const char*);
  FILE* yyin;
  extern line* lineList;
%}

%output "parser.c"
%defines "parser.h"

%union{
  Line *line;
  Symbol_Literal_List * sym_lit_list;
  std::vector<std::string*> list_of_symbols;
  std::string *symbol;
  Directive* dir;
  Instruction* ins;
  Label* lbl;
  JumpOperand* jmpOp;
  DataOperand* dataOp;
  short reg;
  int number;
  int token;
}

%token<reg> REGISTER;
%token<symbol> SYMBOL;
%token<number> NUMBER;
%token<token> GLOBAL,EXTERN,SECTION,WORD,SKIP,ASCII,EQU,END;
%token<token> HALT,INT,IRET,RET,CALL,JMP,JGT,JEQ,JNE,PUSH,POP,XCHG,ADD,SUB,MUL,DIV,CMP,NOT,AND,OR,XOR;
%token<token> TEST,SHL,SHR,LDR,STR,PLUS,COMMENT,PERCENT,STAR,DOLLAR,LEFT_BR,RIGHT_BR,COLON,SEMI_COLON;
%token<token> NEW_LINE;
%token<token> COMMA;


%type<line> line;
%type<list_of_symbols> list_of_symbols;
%type<sym_lit_list> list_of_symbols_and_literals;
%type<dir> directive;
%type<ins> instruction;
%type<lbl> label;
%type<dataOp> operandData;
%type<jmpOp> operandJump;





%start code



%%
code:
  lines{
    Lines::initLines();
  }
  ;
lines:
  line{
    if($1 != nullptr){
      Lines::addLine($1);
    }
  }
  |
  lines line{
    if($2 != nullptr){
      Lines::addLine($2);
    }
  }
  ;
line:
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
    $$ = new Directive(DirectiveName.GLOBAL,*$2);
    delete $2;
  }
  |
  EXTERN list_of_symbols{
    $$ = new Directive(DirectiveName.EXTERN,*$2);
    delete $2;
  }
  |
  SECTION SYMBOL{
    $$ = new Directive(DirectiveName.SECTION,$2);
  }
  |
  WORD list_of_symbols_and_literals{
    $$ = new Directive(DirectiveName.WORD,*$2);
    delete $2;
  }
  |
  SKIP NUMBER{
    $$ = new Directive(DirectiveName.SKIP,$2);
  }
  |
  END{
    $$ = new Directive(DirectiveName.END);
  }
  ;

instruction:
  HALT{
      $$ = new Instruction(InstructionName.HALT);
  }
  |
  INT REGISTER{
       $$ = new Instruction(InstructionName.INT,$2);
  }
  |
  IRET{
    $$ = new Instruction(InstructionName.IRET);
  }
  |
  CALL operandJump{
    $$ = new Instruction(InstructionName.CALL,$2);
  }
  |
  RET{
    $$ = new Instruction(InstructionName.RET);
  }
  |
  JMP operandJump{
    $$ = new Instruction(InstructionName.JMP,$2);
  }
  |
  JGT operandJump{
    $$ = new Instruction(InstructionName.JGT,$2);
  }
  |
  JEQ operandJump{
    $$ = new Instruction(InstructionName.JEQ,$2);
  }
  |
  JNE operandJump{
    $$ = new Instruction(InstructionName.JNE,$2);
  }
  |
  PUSH REGISTER{
      $$ = new Instruction(InstructionName.PUSH,$2);
  }
  |
  POP REGISTER{
      $$ = new Instruction(InstructionName.POP,$2);
  }
  |
  XCHG REGISTER COMMA  REGISTER{
      $$ = new Instruction(InstructionName.XCHG,$2,$4);
  }
  |
  ADD REGISTER COMMA  REGISTER{
      $$ = new Instruction(InstructionName.ADD,$2,$4);
  }
  |
  SUB REGISTER COMMA REGISTER{
      $$ = new Instruction(InstructionName.SUB,$2,$4);
  }
  |
  MUL REGISTER COMMA REGISTER{
      $$ = new Instruction(InstructionName.MUL,$2,$4);
  }
  |
  DIV REGISTER COMMA REGISTER{
      $$ = new Instruction(InstructionName.DIV,$2,$4);
  }
  |
  CMP REGISTER COMMA REGISTER{
      $$ = new Instruction(InstructionName.CMP,$2,$4);
  }
  |
  NOT REGISTER{
      $$ = new Instruction(InstructionName.NOT,$2);
  }
  |
  AND REGISTER COMMA REGISTER{
      $$ = new Instruction(InstructionName.AND,$2,$4);
  }
  |
  OR REGISTER COMMA REGISTER{
      $$ = new Instruction(InstructionName.OR,$2,$4);
  }
  | 
  XOR REGISTER COMMA REGISTER{
      $$ = new Instruction(InstructionName.XOR,$2,$4);
  }
  |
  TEST REGISTER COMMA REGISTER{
      $$ = new Instruction(InstructionName.TEST,$2,$4);
  }
  |
  SHL REGISTER COMMA REGISTER{
      $$ = new Instruction(InstructionName.SHL,$2,$4);
  }
  |
  SHR REGISTER COMMA REGISTER{
      $$ = new Instruction(InstructionName.SHR,$2,$4);
  }
  |
  LDR REGISTER operandData{
      $$ = new Instruction(InstructionName.LDR,$2,$4);
  }
  |
  STR REGISTER operandData{
      $$ = new Instruction(InstructionName.STR,$2,$4);
  }
  ;
operandData:
  DOLLAR NUMBER{
    $$ = new DataOperand(DataOperandType.LIT_VALUE,$2);
  }
  |
  DOLLAR SYMBOL{
      $$ = new DataOperand(DataOperandType.SYM_VALUE,$2);
  }
  |
  NUMBER{
      $$ = new DataOperand(DataOperandType.LIT_MEMORY,$1);
  }
  |
  SYMBOL{
      $$ = new DataOperand(DataOperandType.SYM_MEMORY,$1);
  }
  |
  PERCENT SYMBOL{
      $$ = new DataOperand(DataOperandType.SYM_RELATIVE,$2);
  }
  |
  REGISTER{
      $$ = new DataOperand(DataOperandType.REG_VALUE,$1);
  }
  |
  LEFT_BR REGISTER RIGHT_BR{
      $$ = new DataOperand(DataOperandType.REG_MEMORY,$2);
  }
  |
  LEFT_BR REGISTER PLUS NUMBER RIGHT_BR{
      $$ = new DataOperand(DataOperandType.REG_LITERAL,$2,$4);
  }
  |
  LEFT_BR REGISTER PLUS SYMBOL RIGHT_BR{
      $$ = new DataOperand(DataOperandType.REG_SYMBOL,$2,$4);
  }
  ;

operandJump:
  NUMBER{
      $$ = new JumpOperand(JumpOperandType.LIT_VAL,$1);
  }
  |
  SYMBOL{
      $$ = new JumpOperand(JumpOperandType.ABS_SYM,$1);
  }
  |
  PERCENT SYMBOL{
      $$ = new JumpOperand(JumpOperandType.REL_SYM,$2);
  }
  STAR NUMBER{
      $$ = new JumpOperand(JumpOperandType.LIT_MEM,$2);
  }
  |
  STAR SYMBOL{
      $$ = new JumpOperand(JumpOperandType.SYM_MEM,$2);
  }
  |
  STAR REGISTER{
      $$ = new JumpOperand(JumpOperandType.REG_VAL,$2);
  }
  |
  STAR LEFT_BR REGISTER RIGHT_BR{
      $$ = new JumpOperand(JumpOperandType.REG_MEM,$3);
  }
  |
  STAR LEFT_BR REGISTER PLUS SYMBOL RIGHT_BR{
      $$ = new JumpOperand(JumpOperandType.REG_SYM,$3,$5);
  }
  |
  STAR LEFT_BR REGISTER PLUS NUMBER RIGHT_BR{
      $$ = new JumpOperand(JumpOperandType.REG_LIT,$3,$5);
  }
  ;

label:
  SYMBOL COLON{
    $$ = new Label($1);
  }
  ;

list_of_symbols:
  SYMBOL{
      $$ = new std::vector<std::string*>();
      $$->push_back($1);
      delete $1;
  }
  |
  list_of_symbols COMMA SYMBOL{
      $$->push_back($3);
      delete $3;
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
  list_of_symbols_and_literals COMMA NUMBER{
      $$->pushLiteral($3);
  }
  ;
  


%%