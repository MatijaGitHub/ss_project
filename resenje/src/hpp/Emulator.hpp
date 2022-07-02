#pragma once
#include <string>
#include "limits.h"
#include <iomanip>
#include <iostream>
#include <fstream>
#include <istream>
#include <unordered_map>
#include <vector>

typedef short REGISTER;
typedef unsigned short SYSTEM_REGISTER;
#define PC_REG 7
enum ADDR_MODE{
  IMMED_ADR,REGDIR_ADR,REGDIR16_ADR,REGIND_ADR,REGIND16_ADR,MEM_ADR
};
enum UP_MODE{
  NO_UPDATE,PRE_DEC,PRE_INC,POST_DEC,POST_INC
};
class Emulator{
  private:
    unsigned char* memory;
    void loadIntoMemory(std::string inputFile);
    SYSTEM_REGISTER psw;
    REGISTER registers[8] = {0,0,0,0,0,0,0,0};
    char intr_enabled[8] = {0,0,0,0,0,0,0,0};
    bool working;
    void init();
    void haltInstruction();
    void intInstruction();
    void iretInstruction();
    void callInstruction();
    void retInstruction();
    void jmpInstruction();
    void jeqInstruction();
    void jneInstruction();
    void jgtInstruction();
    void loadInstruction();
    void storeInstruction();
    void xchgInstruction();
    void addInstruction();
    void subInstruction();
    void mulInstruction();
    void divInstruction();
    void cmpInstruction();
    void notInstruction();
    void andInstruction();
    void orInstruction();
    void xorInstruction();
    void testInstruction();
    void shlInstruction();
    void shrInstruction();

    std::unordered_map<char,bool> opCodes;
    std::unordered_map<char,ADDR_MODE> addressModes;
    std::unordered_map<char,UP_MODE> upModes;
    void handleInterrupts();


  public:
    Emulator();
    void start(std::string inputFile);
    


};