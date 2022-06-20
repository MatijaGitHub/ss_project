#pragma once
#include "../../misc/hpp/Lines.hpp"
#include <string>

class Assembler{
public:
  Assembler(std::string input);
  Assembler(std::string input, std::string output);
  int assemble();
protected:
  std::string inputFile;
  std::string outputFile;
private:
  int init();
  void reset();
  int firstPass();
  void handleDirective(Directive* directive);
};