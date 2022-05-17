#include "./helper.h"





void addLine(line* line);
line* createLine(char* label,char* dir,instruction* ins);
instruction* createInstruction(char* opCode,char* reg1,char* reg2,operand* operand);
operand* createOperand(int isData,enum dataType data,enum jmpType jmp,char* literal,char* reg,char* symbol);
int isOpcode(const char* opcode);
int isRegister(const char* reg){
  if(strcmp(reg,"r0")==0 || strcmp(reg,"r1")==0 
  || strcmp(reg,"r2")==0 || strcmp(reg,"r3")==0 
  || strcmp(reg,"r4")==0 || strcmp(reg,"r5")==0 
  || strcmp(reg,"r6")==0 || strcmp(reg,"r7")==0 
  || strcmp(reg,"sp")==0 || strcmp(reg,"pc")==0 
  || strcmp(reg,"psw")==0) return 1;
  return 0;
}


int isDirective(const char* dir){
  if(strcmp(dir,"global")==0 || strcmp(dir,"extern")==0 
    || strcmp(dir,"section")==0 || strcmp(dir,"word")==0 
    || strcmp(dir,"skip")==0 || strcmp(dir,"ascii")==0
    || strcmp(dir,"equ")==0 || strcmp(dir,"end")==0)return 1;
  return 0;
}