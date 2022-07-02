#pragma once
#include <string>
#include "limits.h"
#include <iomanip>
#include <iostream>
#include <fstream>
#include <istream>

typedef short REGISTER;
typedef unsigned short SYSTEM_REGISTER;

class Emulator{
  private:
    unsigned char* memory;
    void loadIntoMemory(std::string inputFile);
    SYSTEM_REGISTER psw;
    REGISTER registers[8] = {0,0,0,0,0,0,0,0};
    short intr_enabled;
    bool working;


  public:
    Emulator();
    void start(std::string inputFile);
    


};