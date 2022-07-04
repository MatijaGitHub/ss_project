#include "../hpp/TerminalOutputThread.hpp"



TerminalOutputThread::TerminalOutputThread(Emulator* emulator){
  this->myEmulator = emulator;
  
}

void TerminalOutputThread::run(){
  while (true)
  {
    short character = 0;
    while(character == 0){
      character = *((short*)(this->myEmulator->memory + 0xFF00));
    }
    *((short*)(this->myEmulator->memory + 0xFF00)) = 0;
    putc(character,stdout);
  }
}