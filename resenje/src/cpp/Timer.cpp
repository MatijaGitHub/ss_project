#include "../hpp/Timer.hpp"
#include <chrono>
#include <thread>



Timer::Timer(Emulator* emulator){
  this->myEmulator = emulator;
  
}
unsigned long getTime(short time){
  switch (time)
  {
  case 0:
    return 500;
  case 1:
    return 1000;
  case 2:
    return 1500;
  case 3:
    return 2000;
  case 4:
    return 5000;
  case 5:
    return 10000;
  case 6:
    return 30000;
  case 7:
    return 60000;
  
  default:
    return 0;
  }
}
void Timer::run(){
  while (true)
  {
    short time = *((short*)(this->myEmulator->memory + 0xFF10));
    unsigned long sleepTime = getTime(time);
    std::this_thread::sleep_for(std::chrono::milliseconds(sleepTime));
    this->myEmulator->intr_enabled[3] = 1;
    
  }
}
