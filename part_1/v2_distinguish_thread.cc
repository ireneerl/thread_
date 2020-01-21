#include <thread>
#include <iostream>
#include <vector>

void getID(){
  std::cout << "the thread ID -> " << std::this_thread::get_id()<< '\n';
}

int main(){
  std::vector<std::thread> threads;

  for (int i = 0 ; i < 5 ; i ++){
    threads.push_back(std::thread(getID));
  }

  for (auto& thread : threads){ // auto& -> The compiler will inferer the right type of the variable that is being used. : it's a range based for, It means that loop will parse each element inside threads vector
    thread.join();
  }

  return 0;
}

// RESULT EXAMPLE:
// the thread ID -> 0x70000bd39000
// the thread ID -> 0x70000bdbc000
// the thread ID -> the thread ID -> the thread ID -> 0x70000bcb6000
// 0x70000be3f000
// 0x70000bc33000
// INSTEAD OF
// the thread ID -> 0x70000bd39000
// the thread ID -> 0x70000bdbc000
// the thread ID -> 0x70000bcb6000
// the thread ID -> 0x70000be3f000
// the thread ID -> 0x70000bc33000
// This is because of interleaving. You have no way to control the order of execution of threads.
