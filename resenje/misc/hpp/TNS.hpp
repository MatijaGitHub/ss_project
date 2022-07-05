#pragma once
#include <string.h>
#include "./Expression.hpp"

class TNS{
public:
std::string symbol;
Expression* exp;
TNS* nextTNS;
};