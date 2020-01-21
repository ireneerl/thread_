#include <thread>
#include <iostream>
#include <vector>

int main (){
  std::vector<std::thread> threads;

  for (int i = 0 ; i < 5 ; i ++){
    threads.push_back(std::thread([](){
      std::cout << "the thread ID -> " << std::this_thread::get_id()<< '\n';
    }));
  }

  for(auto& thread: threads){
    thread.join();
  }
  return 0;
}
