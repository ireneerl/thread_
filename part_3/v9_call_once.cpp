#include <thread>
#include <chrono>
#include <iostream>
#include <mutex>

std::mutex mutex;
std::once_flag flag;

void do_something(){
  std::call_once(flag, [](){std::cout << "called once tid : " << std::this_thread::get_id() <<'\n';});
  mutex.lock();
  std::cout << "hello --- " << std::this_thread::get_id() << '\n';
  mutex.unlock();
}

int main(){
  std::thread t1(do_something);
  std::thread t2(do_something);
  std::thread t3(do_something);
  std::thread t4(do_something);

  t1.join();
  t2.join();
  t3.join();
  t4.join();

}
