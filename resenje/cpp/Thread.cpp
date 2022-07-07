#include "../hpp/Thread.hpp"



Thread::Thread()
{
}

Thread::~Thread()
{
}


void Thread::start(){
    if(thread)
        delete thread;
    thread = new std::thread([this](){run();});
    
}

void Thread::join(){
    thread->join();
    
}

void Thread::exit(){
    pthread_cancel(thread->native_handle());
    
}