#pragma once
#include <string>



class Emulator{
  private:
    char* memory;

  public:
    Emulator();
    void loadIntoMemory(std::string inputFile);


};