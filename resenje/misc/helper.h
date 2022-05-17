#pragma once
#include <string.h>
#include <stdlib.h>
#include <stdio.h>



enum dataType{literalVal,symbolVal,literalMem,symbolMem,symbolRel,regVal,regMem,rPlMem,rPsMem,noType};
enum jmpType{literalVa,symbolAbs,symbolRe,literalMe,symbolMe,regVa,regMe,rPlMe,rPsMe,noTyp};

typedef struct 
{
  int isData;
  enum dataType data;
  enum jmpType jmp;
  char* literal;
  char* reg;
  char* symbol;
  
}operand;
typedef struct 
{
  char* opCode;
  char* reg1;
  char* reg2;
  operand* operand;
} instruction;
typedef struct lin 
{
  char* label;
  char* dir;
  instruction* ins;
  struct lin* next;

} line;







int isOpcode(const char* opcode);
int isRegister(const char* reg);
int isDirective(const char* dir);



void addLine(line* lin);
line* createLine(char* label,char* dir,instruction* ins);
instruction* createInstruction(char* opCode,char* reg1,char* reg2,operand* operand);
operand* createOperand(int isData,enum dataType data,enum jmpType jmp,char* literal,char* reg,char* symbol);
void printLines();