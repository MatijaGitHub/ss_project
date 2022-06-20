#pragma once
#include "./Directive.hpp"
#include "./Instruction.hpp"
#include "./Label.hpp"



class Line{
public:
  Line(Directive* dir);
  Line(Instruction* ins);
  Line(Label* l, Directive* dir);
  Line(Label* l, Instruction* ins);
  Line(Label* l);
  Line* getNext();
  void setNext(Line* nex);
  void readLine();
  Directive* getDirective();
  Instruction* getInstruction();
  Label* getLabel();
   
private:
  Directive* directive;
  Instruction* instruction;
  Label* label;
  Line* nextLine;

 
};