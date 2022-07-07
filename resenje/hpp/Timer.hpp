#pragma once
#include "./Thread.hpp"
#include "./Emulator.hpp"
#include <mutex>
#include <stdio.h>


class Timer :public Thread{
public:
  Timer(Emulator* emulator);
  
private:
  std::mutex mutexTime;
  Emulator* myEmulator;
protected:
  virtual void run();



};