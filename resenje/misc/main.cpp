#include "../src/hpp/Assembler.hpp"
#include "../src/hpp/Linker.hpp"
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <stdio.h>



int main(int argc, char *argv[])
{
  // if(argc < 2 || argc == 3 || argc > 4) return -1;
  // std::string outputName = "default.o";
  // std::string inputName;
  // bool isOutput = false;
  // for(int i = 1;i < argc; i++){
  //     std::string arg(argv[i]);
  //     if(arg == "-o") {
  //       isOutput = true;
  //       continue;
  //     }
  //     if(isOutput){
  //       outputName = arg;
  //       isOutput = false;
  //     }
  //     else{
  //       inputName = arg;
  //     }
        
  // }   
  // Assembler * as = new Assembler(inputName,outputName);
  // int res = as->assemble();
  //as->objDump();
  std::vector<std::string> links;
  for(int i = 1; i< argc; i++){
      std::string arg(argv[i]);
      links.push_back(arg);
  }
  Linker linker = Linker();
  linker.readELFS(links);
  return 1;
}