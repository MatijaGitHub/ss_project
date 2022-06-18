#include <string>



class Label{
  public:
  Label(std::string lab);
  std::string getLabel();


  private:
    std::string label;
};