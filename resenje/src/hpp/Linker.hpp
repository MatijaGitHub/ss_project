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
  std::unordered_map<std::string, std::vector<std::pair<int,std::string>>> sectionContents;
  std::unordered_map<std::string, RelocationTable*> relocationTables;
  std::unordered_map<std::string,unsigned short> placedSections;
  std::unordered_map<std::string,unsigned short> mappedSections;
  std::set<std::string> externSymbols;
  int numOfSymbols;
  int numOfSections;
  int numOfRelocations;
  void skipLines(int n, std::ifstream* file);
  void checkIfSymbolIsDefined(std::string name);
  void readELF(std::string fileName);
  void checkIfPlacementPossible(unsigned short min,unsigned short max);
  /////////////
  void readELFS(std::vector<std::string> files);
  void map();
  void resolveSymbols();
  void exoneration();
  public:
  Linker();
  void link(std::vector<std::string> files);
  void placeSection(std::string command);

  
};