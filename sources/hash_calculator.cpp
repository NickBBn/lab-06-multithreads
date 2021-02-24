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
      if (json_struct){
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

const std::string timestamp_str = "Timestamp";
const std::string hash_str = "Hash";
const std::string data_str = "Data";

void hash_calculator::print_to_json(const std::string &data, const std::string &hash){
  json_struct->json->emplace_back( nlohmann::json{
    {hash_str, hash},
    {data_str, data}
  });
}
