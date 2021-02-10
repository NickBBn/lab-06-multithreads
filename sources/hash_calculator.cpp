#include "hash_calculator.hpp"

void hash_calculator::calculate_hash() {
  //std::cout << "Thread id : " << std::this_thread::get_id() << std::endl;
  ++(*a);
  std::cout << "a = " << *a << std::endl;
  BOOST_LOG_TRIVIAL(trace) << "A trace from thread, " << *a;
}
