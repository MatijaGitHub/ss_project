#include "../hpp/TerminalInputThread.hpp"
#include <stdio.h>
#include <unistd.h>
#include <termios.h>

int getch() {
   struct termios oldtc;
   struct termios newtc;
   int ch;
   tcgetattr(STDIN_FILENO, &oldtc);
   newtc = oldtc;
   newtc.c_lflag &= ~(ICANON | ECHO);
   tcsetattr(STDIN_FILENO, TCSANOW, &newtc);
   ch=getchar();
   tcsetattr(STDIN_FILENO, TCSANOW, &oldtc);
   return ch;
}

TerminalInputThread::TerminalInputThread(Emulator* emulator){
  this->myEmulator = emulator;
  
}

void TerminalInputThread::run(){
  while (true)
  {
    short input = getch();
    *((short*)(this->myEmulator->memory + 0xFF02)) = input;
    this->myEmulator->intr_enabled[2] = 1;
  }
}