#include "../hpp/Section.hpp"



Section::Section(){
  this->locationCounter = 0;
  this->sectionName = "";
  this->sectionContent = "";
  this->myEntry = nullptr;
  this->sectionContentCounter = 0;
}

void Section::writeOneByteContent(std::string byte){
  this->sectionContent+=byte;
  if(this->sectionContentCounter++ == 7){
    this->sectionContent+="\n";
    this->sectionContentCounter = 0;
  }
  else{
    this->sectionContent+=" ";
  }
}
void Section::writeTwoByteContent(std::string twobyte){
  std::string firstByte = twobyte.substr(0, twobyte.find(" "));
  std::string secondByte = twobyte.substr(twobyte.find(" ")+1);
  writeOneByteContent(firstByte);
  writeOneByteContent(secondByte);
}
void Section::readContent(){
  printf("%s\n",this->sectionContent.c_str());
  printf("Section %s read!\n",this->sectionName.c_str());
}

