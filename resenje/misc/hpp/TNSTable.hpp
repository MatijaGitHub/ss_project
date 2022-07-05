#pragma once
#include "./TNS.hpp"

class TNSTable{
public:
TNS* head;
TNS* tail;
TNSTable();
void addToTNS(std::string,Expression* exp);
void printTNS();


};