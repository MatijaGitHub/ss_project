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

  Linker linker = Linker();
  std::vector<std::string> links;
  bool isOutputArg = false;
  for(int i = 1; i< argc; i++){
      std::string arg(argv[i]);
      if(arg.at(0) == '-' && arg.at(1) == 'p'){
          linker.placeSection(arg);
      }
      else if(arg.at(0) == '-' && arg.at(1) == 'o'){
          isOutputArg = true;
      }
      else if(arg.at(0) == '-' && arg.at(1) == 'h'){
        linker.setToHex();
      }
      else if(!isOutputArg){
        links.push_back(arg);
      }
      else{
        linker.setOutput(arg);
        isOutputArg = false;
      }
  }
  
  linker.link(links);
  
  return 1;
}