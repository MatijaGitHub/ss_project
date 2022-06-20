#pragma once
#include "./Line.hpp"
class Lines{
  public:
  static Line* readLine();
  static void writeLine(Line* line); 
  static void initLines();
  static void readLines();
  static Line* getHead();
  private:
  static Line* head;
  static Line* tail;
  
};