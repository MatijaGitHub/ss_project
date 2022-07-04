#pragma once
#include <thread>


class Thread
{
  public:
std::thread *thread = nullptr;
  Thread();
  ~Thread();
  void start();
  void join();
  void exit();
  virtual void run() = 0;
};

