#include <iostream>
#include <vector>
#include <thread>


struct MyException : public std::exception
{
  const char * what () const throw ()
  {
    return "Value cannot be less than 0";
  }
};

struct Counter {
  std::mutex mutex; //safe point
  int value;

  Counter() : value(100){}

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
    mutex.lock();
    counter.increment();
    mutex.unlock();
  }

  void decrement(){
    mutex.lock();
    try{
      counter.decrement();
    }catch(MyException& e){
      mutex.unlock();
      std::cout << e.what() << std::endl;
    }
    mutex.unlock();
  }
};

int main(){
  ConcurrentCounter counter;
  std::vector<std::thread> threads;
  for(int i = 0 ; i < 5; i++){
    threads.push_back(std::thread([&counter](){
      for(int i = 0 ; i < 100 ; i++){
        counter.decrement();
      }
    }));
  }

  for(auto& thread: threads){
    thread.join();
  }

  std::cout << counter.counter.value << std::endl;

  return 0;
}
