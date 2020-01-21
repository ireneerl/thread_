#include <iostream>
#include <vector>
#include <thread>

struct Counter {
  std::mutex mutex; //safe point
  int value;

  Counter() : value(0){}

  void increment(){
    mutex.lock(); //safe point
    ++value;
    mutex.unlock(); //safe point
  }
};
int main(){
  Counter counter;
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

  std::cout << counter.value << std::endl;

  return 0;
}
