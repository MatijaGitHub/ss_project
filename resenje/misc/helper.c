#include "./helper.h"



line* lineList = NULL;

void addLine(line* lin){
  if(lineList == NULL) lineList = lin;
  else{
    line* pom = lineList;
    while(pom->next!=NULL){
      pom = pom->next;
    }
    pom->next = lin;
  }
}


line* createLine(char* label,char* dir,instruction* ins){
  line* lin = malloc(sizeof(line));
  lin->label = label;
  lin->dir = dir;
  lin->ins = ins;
  lin->next = NULL;
  return lin;
}



instruction* createInstruction(char* opCode,char* reg1,char* reg2,operand* operand){
  instruction* ins = malloc(sizeof(instruction));
  ins->opCode = opCode;
  ins->reg1 = reg1;
  ins->reg2 = reg2;
  ins->operand = operand;
}



operand* createOperand(int isData,enum dataType data,enum jmpType jmp,char* literal,char* reg,char* symbol){
  operand* opr = malloc(sizeof(operand));
  opr->isData = isData;
  opr->data = data;
  opr->jmp = jmp;
  opr->literal = literal;
  opr->reg = reg;
  opr->symbol = symbol;
  return opr;
}





int isOpcode(const char* opcode){
  if(strcmp(opcode,"halt")==0 || strcmp(opcode,"int")==0 
  || strcmp(opcode,"iret")==0 || strcmp(opcode,"call")==0 
  || strcmp(opcode,"ret")==0 || strcmp(opcode,"jmp")==0 
  || strcmp(opcode,"jeq")==0 || strcmp(opcode,"jne")==0 
  || strcmp(opcode,"jgt")==0 || strcmp(opcode,"push")==0 
  || strcmp(opcode,"pop")==0 || strcmp(opcode,"xchg")==0 
  || strcmp(opcode,"add")==0 || strcmp(opcode,"sub")==0 
  || strcmp(opcode,"mul")==0 || strcmp(opcode,"div")==0 
  || strcmp(opcode,"cmp")==0 || strcmp(opcode,"not")==0 
  || strcmp(opcode,"and")==0 || strcmp(opcode,"or")==0 
  || strcmp(opcode,"xor")==0 || strcmp(opcode,"test")==0 
  || strcmp(opcode,"shl")==0 || strcmp(opcode,"shr")==0 
  || strcmp(opcode,"ldr")==0 || strcmp(opcode,"str")==0) return 1;
  return 0; 
}
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


void printLines(){
  if(lineList == NULL){
    printf("Nema linija!\n");
    return;
  }
  line* pom = lineList;
  do{
    if(pom->dir!=NULL)printf(pom->dir);
    if(pom->label!=NULL)printf(pom->label);
    if(pom->ins!=NULL)printf(pom->ins->opCode);
    pom = pom->next;
  }while (pom!=NULL);
  
  
}