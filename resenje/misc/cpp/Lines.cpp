#include "../hpp/Lines.hpp"


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
    tail->setNext(line);
    tail = tail->getNext();
}

void Lines::readLines(){

}