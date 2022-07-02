#pragma once
#include "./SymbolTable.hpp"
#include "./Section.hpp"
#include "./RelocationTable.hpp"
#include "./RelocationTableEntry.hpp"
#include <string>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <istream>
#include <unordered_map>
#include <vector>
#include <set>
#include <limits.h>
#include <bits/stdc++.h>


class Linker{
  private:
  SymbolTable* symbolTable;
  std::vector<std::string> orderOfSections;
  std::unordered_map<std::string, std::vector<std::pair<int,std::string>>> sectionContents;
  std::unordered_map<std::string, RelocationTable*> relocationTables;
  std::unordered_map<std::string,unsigned short> placedSections;
  std::unordered_map<std::string,unsigned short> mappedSections;
  std::unordered_map<std::string,int> sectionAppearances;
  std::set<std::string> externSymbols;
  int numOfSymbols;
  int numOfSections;
  int numOfRelocations;
  void skipLines(int n, std::ifstream* file);
  void checkIfSymbolIsDefined(std::string name);
  void readELF(std::string fileName);
  void checkIfPlacementPossible(unsigned short min,unsigned short max, std::string sectionName);
  /////////////
  void readELFS(std::vector<std::string> files);
  void map();
  void resolveSymbols();
  void exoneration();
  void hex();
  public:
  Linker();
  void link(std::vector<std::string> files);
  void placeSection(std::string command);

  
};