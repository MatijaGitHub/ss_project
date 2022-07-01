#pragma once
#include "./SymbolTable.hpp"
#include "./Section.hpp"
#include "./RelocationTable.hpp"
#include <string>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <istream>
#include <unordered_map>
#include <vector>
#include <set>
#include <limits.h>


class Linker{
  private:
  SymbolTable* symbolTable;
  std::unordered_map<std::string, int> sectionSizes;
  std::unordered_map<std::string, std::vector<std::pair<int,std::string>>> sectionContents;
  std::unordered_map<std::string, RelocationTable*> relocationTables;
  std::unordered_map<std::string,short> placedSections;
  std::unordered_map<std::string,short> mappedSections;
  std::set<std::string> externSymbols;
  int numOfSymbols;
  int numOfSections;
  int numOfRelocations;
  void skipLines(int n, std::ifstream* file);
  void checkIfSymbolIsDefined(std::string name);
  void readELF(std::string fileName);
  public:
  
  Linker();
  void readELFS(std::vector<std::string> files);
  void map();
  void placeSection(std::string command);
  void resolveSymbols();
  void exoneration();
  
};