#include <thread>
#include <iostream>
#include <vector>
#include <mutex>

struct complex{
  std::recursive_mutex mutex;
  int i;

  complex(): i(1){}

  void mul(int x){
    std::lock_guard<std::recursive_mutex> lock(mutex);
    i*=x;
  }

  void div(int y){
    std::lock_guard<std::recursive_mutex> lock(mutex);
    i/=y;
  }

  void both(int x, int y){
    std::lock_guard<std::recursive_mutex> lock(mutex);
    mul(x);
    div(y);
  }
};



int main(){
  complex complex;
  complex.both(32, 2);
  std::cout << complex.i << std::endl;
  return 0;
}
