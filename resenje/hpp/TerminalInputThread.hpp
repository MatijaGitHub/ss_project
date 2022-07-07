#pragma once
#include "./Thread.hpp"
#include "./Emulator.hpp"
#include <mutex>
#include <stdio.h>


class TerminalInputThread :public Thread{
public:
  TerminalInputThread(Emulator* emulator);

private:
  std::mutex mutexWrite;
  Emulator* myEmulator;
protected:
  virtual void run();

};

