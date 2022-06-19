#include "../hpp/Lines.hpp"

Line* Lines::head = nullptr;
Line* Lines::tail = nullptr;

void Lines::initLines(){
  head = nullptr;
  tail = nullptr;
}

Line* Lines::readLine(){
    Line* ret = head;
    head = head->getNext();
    return ret;
}

void Lines::writeLine(Line* line){
    if(tail == nullptr){
      head = line;
      tail = line;
    }
    else{
      tail->setNext(line);
      tail = tail->getNext();
    }
}

void Lines::readLines(){
    Line* curr = head;
    while(curr!=nullptr){
      printf("%s",curr->readLine().c_str());
      curr = curr->getNext();
    }
}