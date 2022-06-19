#include "../hpp/Line.hpp"

Line::Line(Directive* dir){
  this->directive = dir;
  this->label = nullptr;
  this->instruction = nullptr;
  this->nextLine = nullptr;
}

Line::Line(Instruction* ins){
  this->instruction = ins;
  this->label = nullptr;
  this->directive = nullptr;
  this->nextLine = nullptr;
}

Line::Line(Label* l, Directive* dir){
  this->label = l;
  this->directive = dir;
  this->instruction = nullptr;
  this->nextLine = nullptr;
}

Line::Line(Label* l, Instruction* ins){
  this->label = l;
  this->instruction = ins;
  this->directive = nullptr;
  this->nextLine = nullptr;
}

Line::Line(Label* l){
  this->label = l;
  this->directive = nullptr;
  this->instruction = nullptr;
  this->nextLine = nullptr;
}

void Line::setNext(Line* nex){
  this->nextLine = nex;
}

Line* Line::getNext(){
  return this->nextLine;
}

void Line::readLine(){
  if(this->instruction!=nullptr){
    printf("%s\n",this->instruction->getInstrNameString().c_str());
  }
  if(this->directive!=nullptr){
    printf("%s\n",this->directive->getDirNameString().c_str());
  }
}