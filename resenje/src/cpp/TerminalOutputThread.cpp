#include "../hpp/TerminalOutputThread.hpp"



TerminalOutputThread::TerminalOutputThread(Emulator* emulator){
  this->myEmulator = emulator;
  
}

void TerminalOutputThread::run(){
  while (true)
  {
    
    short character = 0;
    //this->mutexRead.try_lock();
    character = *((short*)(this->myEmulator->memory + 0xFF00));
    *((short*)(this->myEmulator->memory + 0xFF00)) = 0;
    //this->mutexRead.unlock();
    
    
    putc(character,stdout);
  }
}