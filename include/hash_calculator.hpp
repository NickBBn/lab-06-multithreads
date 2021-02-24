//
// Created by nickmint on 1/26/21.
//

#ifndef MULTITHREADS_HASH_CALCULATOR_HPP
#define MULTITHREADS_HASH_CALCULATOR_HPP
#include <thread>
#include <iostream>
#include "boost/log/trivial.hpp"
#include "boost/log/sinks.hpp"
#include "boost/log/core/record.hpp"
#include "boost/log/core.hpp"
#include "boost/log/core/core.hpp"
#include "boost/log/core/record_view.hpp"
#include <boost/log/utility/setup/console.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/sources/logger.hpp>
#include <boost/log/expressions.hpp>
#include <empty_deleter.hpp>
#include <boost/log/expressions/keyword_fwd.hpp>
#include <boost/log/expressions/keyword.hpp>
#include <boost/log/support/date_time.hpp>
#include "../third-party/PicoSHA2/picosha2.h"
#include <fstream>
#include <atomic>
#include <mutex>
#include "nlohmann/json.hpp"

class hash_calculator {
 public:
    int calculate_hash();
    void print_to_json(const std::string &data, const std::string &hash);
  //static std::ofstream* json_file;
  static std::atomic<bool> close_threads;
  static std::mutex json_mutex;
  static struct json_structure{
      nlohmann::json* json;
      std::ofstream* json_file;
      json_structure(const std::string& file_name){
        json_file = new std::ofstream(file_name);
        json = new nlohmann::json;
        *json = nlohmann::json::array();
      }
      ~json_structure(){
        *json_file << json->dump(4);
        if (json) delete json;
        if (json_file){
          if (json_file->is_open()) json_file->close();
          delete json_file;
        }
      }
  } *json_struct;
};

#endif  // MULTITHREADS_HASH_CALCULATOR_HPP
