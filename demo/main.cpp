#include <iostream>
#include <hash_calculator.hpp>
#include <thread>
#include <vector>
/*
void new_thread(std::shared_ptr<hash_calculator> calc){
  std::cout << "thread " << std::this_thread::get_id()
            << " ; a = " << calc->get_a() << std::endl;
  calc->calculate_hash();
}

int main() {
  std::cout << "Hello world" << std::endl;
  std::vector<std::shared_ptr<hash_calculator>> calc_pointers;
  std::shared_ptr<hash_calculator> calc_orig(new hash_calculator);
  calc_pointers.push_back(calc_orig);
  calc_orig->set_a(10);
  std::vector<std::thread> threads;
  for (size_t i = 0; i < 10; ++i)
  {
    std::shared_ptr<hash_calculator> calc(new hash_calculator);
    threads.emplace_back(std::thread(new_thread, calc));
  }
  std::thread thr(new_thread, calc_orig);
  thr.join();
  return 0;
}*/

void calculation() {
  std::cout << "thread " << std::this_thread::get_id() << std::endl;
}

int main(int argc, char* argv[]) {
  unsigned number_of_threads = 0;
  switch (argc){
    case 1 :
      number_of_threads = std::thread::hardware_concurrency();
      break;
    case 2 :
      try {
        number_of_threads = std::stoi(argv[1]);
      } catch (const std::invalid_argument& e) {
        std::cout << "Invalid arguments: argument is not integer " << std::endl;
        return -1;
      }
      break;
    default:
      std::cout << "invalid arguments" << std::endl;
      return -1;
  }
  std::cout << "Recommended number of threads: "
            << std::thread::hardware_concurrency() << std::endl
            << "number of threads: " << number_of_threads << std::endl;
  std::vector<std::thread> threads;
  for (unsigned i = 0; i < number_of_threads; ++i){
    threads.emplace_back(std::thread(calculation));
  }
  for (auto& thread : threads)
  {
    thread.join();
  }
  return 0;
}