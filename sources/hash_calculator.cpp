#include "hash_calculator.hpp"

namespace src = boost::log::sources;

void hash_calculator::calculate_hash() {
  //std::cout << "Thread id : " << std::this_thread::get_id() << std::endl;
  ++(*a);
  std::cout << "a = " << *a << std::endl;
  BOOST_LOG_TRIVIAL(error) << "A trace from thread, " << *a;
}
