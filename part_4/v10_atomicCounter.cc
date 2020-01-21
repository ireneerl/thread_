#include <thread>
#include <iostream>
#include <atomic>
#include <vector>

struct AtomicCounter{
  std::atomic<int> value;

  AtomicCounter(): value(0){}

  void increment(){
    ++value;
  }
  void decrement(){
    --value;
  }
  int get(){
    return value.load();
  }
};

int main(){
  AtomicCounter a_counter;

  std::vector<std::thread> threads;
  for(int i = 0; i < 10 ; i++){
    threads.push_back(std::thread([&a_counter](){
      for(int i = 0; i < 500;i++){
        a_counter.increment();
      }
    }));
  }

  for (auto& thread: threads){
    thread.join();
  }

  std::cout << a_counter.get() << '\n';

  return 0;
}
