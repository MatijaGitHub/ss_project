#pragma once
#include "./Thread.hpp"
#include "./Emulator.hpp"
#include <mutex>
#include <stdio.h>


class TerminalOutputThread : public Thread{
  public:
  TerminalOutputThread(Emulator* emulator);

private:
  std::mutex mutexRead;
  Emulator* myEmulator;
protected:
  virtual void run();
};