#include "hash_calculator.hpp"

const size_t begin_pos = 61;
const size_t length = 3;
const std::string nulls = "000";

int hash_calculator::calculate_hash() {
  while (!close_threads){
    std::string data = std::to_string(std::rand());
    std::string hash = picosha2::hash256_hex_string(data);
    if (hash.substr(begin_pos, length) == nulls){
      BOOST_LOG_TRIVIAL(info) << "Rand: " << data << std::endl << hash;
      if (json_file){
        json_mutex.lock();
        print_to_json(data, hash);
        json_mutex.unlock();
      }
    } else {
      BOOST_LOG_TRIVIAL(trace) << "Rand: " << data << std::endl << hash;
    }
  }
  return 0;
}

void hash_calculator::print_to_json(const std::string &data, const std::string &hash){
  *json_file << data << "    " << hash << std::endl;
}
