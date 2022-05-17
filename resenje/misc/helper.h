typedef struct 
{
  char* label;
  char* dir;
  char* opCode;
  char* reg1;
  char* reg2;
  char* operand;
  line* next;

} line;

bool isOpcode(char* opcode);
bool isRegister(char* reg);
bool isDirective(char* dir);

line* lineList = nullptr;

void addLine(line* line);
line* createLine(char* label,char* dir,char* opCode,char* reg1,char* reg2,char* operand);