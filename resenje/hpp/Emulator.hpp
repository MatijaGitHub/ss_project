#pragma once
#include <string>
#include "limits.h"
#include <iomanip>
#include <iostream>
#include <fstream>
#include <istream>
#include <unordered_map>
#include <vector>
#include <mutex>
#include <semaphore.h>
#include <stdio.h>
#include <unistd.h>
#include <termios.h>
class TerminalInputThread;
class TerminalOutputThread;
class Timer;
typedef short REGISTER;
typedef unsigned short SYSTEM_REGISTER;
#define PC_REG 7
#define PSW 8
#define SP 6
enum ADDR_MODE{
  IMMED_ADR,REGDIR_ADR,REGDIR16_ADR,REGIND_ADR,REGIND16_ADR,MEM_ADR
};
enum UP_MODE{
  NO_UPDATE,PRE_DEC,PRE_INC,POST_DEC,POST_INC
};
class Emulator{
  private:
    SYSTEM_REGISTER psw;
    unsigned char* memory;
    void loadIntoMemory(std::string inputFile);
    bool exitedEmulator;
    sem_t *memoryAccess;
    sem_t *canEndSem;
    REGISTER registers[9] = {0,0,0,0,0,0,0,0,0};
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

    std::unordered_map<char,void(Emulator::*)()> opCodes;
    std::unordered_map<char,ADDR_MODE> addressModes;
    std::unordered_map<char,UP_MODE> upModes;
    
    void handleInterrupts();
    short getOperand(unsigned char adrMode,unsigned char upMod, unsigned char rD, unsigned char rS,bool* isValid,short** operandDest);

  public:
    Emulator();
    void start(std::string inputFile);
    
  
  friend TerminalInputThread;
  friend TerminalOutputThread;
  friend Timer;
  TerminalInputThread* input;
  TerminalOutputThread* output;
  Timer* timer;
};