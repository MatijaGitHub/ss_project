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
  this->sectionContentCounter++;
  if(this->sectionContentCounter == 4){
    this->sectionContent+="\t";
  }
  else if(this->sectionContentCounter == 8){
    this->sectionContent+="\n";
    this->sectionContentCounter = 0;
  }
  else{
    this->sectionContent+=" ";
  }
}
void Section::writeTwoByteContent(std::string twobyte){
  std::string firstByte;
  std::string secondByte;
  if(twobyte.length() == 2){
    firstByte = "00";
    secondByte = twobyte;
  }
  else if(twobyte.length() == 3){
    firstByte = "0";
    firstByte+=twobyte.at(0);
    secondByte = "";
    secondByte+=twobyte.at(1);
    secondByte+=twobyte.at(2);
  }
  else{
    firstByte = "";
    firstByte += twobyte.at(0);
    firstByte += twobyte.at(1);
    secondByte = "";
    secondByte += twobyte.at(2);
    secondByte += twobyte.at(3);
  }
  writeOneByteContent(firstByte);
  writeOneByteContent(secondByte);
}
void Section::readContent(){
  printf("%s\n",this->sectionContent.c_str());
  printf("Section %s read!\n",this->sectionName.c_str());
}

