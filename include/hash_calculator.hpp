//
// Created by nickmint on 1/26/21.
//

#ifndef MULTITHREADS_HASH_CALCULATOR_HPP
#define MULTITHREADS_HASH_CALCULATOR_HPP
#include <thread>
#include <iostream>
#include "boost/log/trivial.hpp"
//#include "boost/log/sources/logger.hpp"
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
#include <boost/log/utility/empty_deleter.hpp>
#include <boost/log/expressions/keyword_fwd.hpp>
#include <boost/log/expressions/keyword.hpp>
#include <boost/log/support/date_time.hpp>

class hash_calculator {
 public:
  void calculate_hash();
  static int* a;
};

#endif  // MULTITHREADS_HASH_CALCULATOR_HPP
