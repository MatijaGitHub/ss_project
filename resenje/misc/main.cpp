#include "../src/hpp/Assembler.hpp"
#include "../src/hpp/Linker.hpp"
#include "../src/hpp/Emulator.hpp"
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
  // as->objDump();
  // Linker linker = Linker();
  // std::vector<std::string> links;
  // bool isOutputArg = false;
  // for(int i = 1; i< argc; i++){
  //     std::string arg(argv[i]);
  //     if(arg.at(0) == '-' && arg.at(1) == 'p'){
  //         linker.placeSection(arg);
  //     }
  //     else if(arg.at(0) == '-' && arg.at(1) == 'o'){
  //         isOutputArg = true;
  //     }
  //     else if(arg.at(0) == '-' && arg.at(1) == 'h'){
  //       linker.setToHex();
  //     }
  //     else if(!isOutputArg){
  //       links.push_back(arg);
  //     }
  //     else{
  //       linker.setOutput(arg);
  //       isOutputArg = false;
  //     }
  // }
  
  // linker.link(links);
  Emulator emulator = Emulator();
  emulator.start("/home/ss/Desktop/ss_project/program.hex");

  return 1;
}