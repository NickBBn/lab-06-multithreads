#include "hash_calculator.hpp"

const size_t begin_pos = 60;
const size_t length = 4;
const std::string nulls = "0000";

[[noreturn]] void hash_calculator::calculate_hash() {
  while (true){
    int data = std::rand();
    std::string hash = picosha2::hash256_hex_string(std::to_string(data));
    if (hash.substr(begin_pos, length) == nulls)
      BOOST_LOG_TRIVIAL(info) << "Rand: " << data << std::endl << hash;
    else
      BOOST_LOG_TRIVIAL(trace) << "Rand: " << data << std::endl << hash;
  }
}
