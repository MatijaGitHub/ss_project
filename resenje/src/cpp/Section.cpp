#include "../hpp/Section.hpp"



Section::Section(){
  this->locationCounter = 0;
  this->sectionName = "";
  this->sectionContent = "";
  this->myEntry = nullptr;
  this->sectionContentCounter = 0;
  this->myRelocationTable = new RelocationTable();
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

void Section::patchContent(unsigned long content, int patch){
  int mask = 0b0000000011111111;
  unsigned firstByte = content;
  firstByte>>=8;
  unsigned secondByte = content&mask;
  std::stringstream stream;
  stream << std::setfill ('0') << std::setw(sizeof(short)) 
         << std::hex << firstByte;
  std::string firstByteWritable = stream.str();
  stream.str("");
  stream << std::setfill ('0') << std::setw(sizeof(short)) 
         << std::hex << secondByte;
  std::string secondByteWritable =  stream.str();
  int location = 0;
  for(int i = 0; i<patch; i++){
      location+=3;
  }
  this->sectionContent.at(location) = firstByteWritable.at(0);
  this->sectionContent.at(location + 1) = firstByteWritable.at(1);
  location+=3;
  this->sectionContent.at(location) = secondByteWritable.at(0);
  this->sectionContent.at(location + 1) = secondByteWritable.at(1);
}
