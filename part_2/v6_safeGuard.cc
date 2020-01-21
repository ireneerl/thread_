#include <thread>
#include <iostream>
#include <vector>
#include <mutex>

struct MyException : public std::exception
{
  const char * what () const throw ()
  {
    return "Value cannot be less than 0";
  }
};

struct Counter{
  int value;

  Counter(): value(0){}

  void increment(){
    ++value;
  }

  void decrement(){
    if(value==0){
      throw MyException();
    }
    --value;
  }
};

struct ConcurrentCounter{
  std::mutex mutex;
  Counter counter;

  void increment(){
    std::lock_guard<std::mutex> guard(mutex);
    counter.increment();
  }

  void decrement(){
    std::lock_guard<std::mutex> guard(mutex);
  }
};


int main(){
  ConcurrentCounter counter;
  std::vector<std::thread> threads;
  for(int i = 0 ; i < 5; i++){
    threads.push_back(std::thread([&counter](){
      for(int i = 0 ; i < 100 ; i++){
        counter.increment();
      }
    }));
  }

  for(auto& thread: threads){
    thread.join();
  }

  std::cout << counter.counter.value << std::endl;

  return 0;
}
