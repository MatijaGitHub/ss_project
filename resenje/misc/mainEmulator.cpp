#include "../hpp/Assembler.hpp"
#include "../hpp/Linker.hpp"
#include "../hpp/Emulator.hpp"
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <stdio.h>



int main(int argc, char *argv[])
{

  if(argc < 1 && argc > 2)exit(-1);
  std::string arg(argv[1]);
  Emulator emulator = Emulator();
  emulator.start(arg);
  exit(0);
  return 1;
}