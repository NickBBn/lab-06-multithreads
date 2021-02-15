#include "hash_calculator.hpp"

namespace src = boost::log::sources;

void hash_calculator::calculate_hash() {
  //std::cout << "Thread id : " << std::this_thread::get_id() << std::endl;
  ++(*a);
  std::cout << "a = " << *a << std::endl;
  //src::logger lg;
  BOOST_LOG_TRIVIAL(info) << "A trace from thread, " << *a;
}
