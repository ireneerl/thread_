#include <thread>
#include <iostream>

void hello(){
  std::cout << "first execution from thread" << std::endl;
}

int main(){
  std::thread t1(hello); //An interesting thing in this first example is the call to the join() function. Calling this function forces the current thread to wait for the other one
  t1.join();
}

// Starting a new thread is very easy.
// When you create an instance of a std::thread, it will automatically be started.
// When you create a thread you have to give it the code it will execute.
// The first choice for that, is to pass it a function pointer.
