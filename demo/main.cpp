#include <iostream>
#include <hash_calculator.hpp>
#include <thread>
#include <vector>

void new_thread(std::shared_ptr<hash_calculator> calc){
  std::cout << "thread " << std::this_thread::get_id()
            << " ; a = " << calc->get_a() << std::endl;
  calc->calculate_hash();
}

int main() {
  std::cout << "Hello world" << std::endl;
  std::shared_ptr<hash_calculator> calc(new hash_calculator);
  calc->set_a(10);
  std::vector<std::thread> q;
  for (size_t i = 0; i < 10; ++i)
  {
    std::shared_ptr<hash_calculator> cal(new hash_calculator);
  }
  std::thread thr(new_thread, calc);
  thr.join();
  return 0;
}