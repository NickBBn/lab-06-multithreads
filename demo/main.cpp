#include <iostream>
#include <hash_calculator.hpp>
#include <thread>
#include <vector>

void calculation() {
  hash_calculator calc;
  calc.calculate_hash();
}

int* hash_calculator::a = nullptr;
void init(){
  boost::log::add_file_log("sample.log");
}

int main(int argc, char* argv[]) {
  init();
  BOOST_LOG_TRIVIAL(trace) << "A trace severity message";
  hash_calculator::a = new int(25);
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
      std::cout << "invalid arguments: program needs one argument" << std::endl;
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
