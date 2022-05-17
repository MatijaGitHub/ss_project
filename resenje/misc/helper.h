#pragma once
#include <string.h>
typedef struct 
{
  char* label;
  char* dir;
  instruction* ins;
  line* next;

} line;
typedef struct 
{
  char* opCode;
  char* reg1;
  char* reg2;
  operand* operand;
} instruction;

typedef struct 
{
  int isData;
  dataType data;
  jmpType jmp;
  char* literal;
  char* reg;
  char* symbol;
  
}operand;
enum dataType{literalVal,symbolVal,literalMem,symbolMem,symbolRel,regVal,regMem,rPlMem,rPsMem,noType};
enum jmpType{literalVal,symbolAbs,symbolRel,literalMem,symbolMem,regVal,regMem,rPlMem,rPsMem,noType};



int isOpcode(const char* opcode);
int isRegister(const char* reg);
int isDirective(const char* dir);

line* lineList = nullptr;

void addLine(line* line);
line* createLine(char* label,char* dir,instruction* ins);
instruction* createInstruction(char* opCode,char* reg1,char* reg2,operand* operand);
operand* createOperand(int isData,dataType data,jmpType jmp,char* literal,char* reg,char* symbol);
