#include "../hpp/TerminalInputThread.hpp"



TerminalInputThread::TerminalInputThread(Emulator* emulator){
  this->myEmulator = emulator;
  
}

void TerminalInputThread::run(){
  while (true)
  {
    short input = getchar();
    printf("IGET\n");
    // this->mutexWrite.lock();
    *((short*)(this->myEmulator->memory + 0xFF02)) = input;
    // this->mutexWrite.unlock();
    this->myEmulator->intr_enabled[2] = 1;
  }
}