#include "../hpp/Label.hpp"

Label::Label(std::string lbl){
  this->label = lbl;
}

std::string Label::getLabel(){
  return this->label;
}

