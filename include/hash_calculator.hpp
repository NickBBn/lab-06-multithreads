//
// Created by nickmint on 1/26/21.
//

#ifndef MULTITHREADS_HASH_CALCULATOR_HPP
#define MULTITHREADS_HASH_CALCULATOR_HPP
#include <thread>
#include <iostream>

class hash_calculator {
 public:
  int get_a() const;
  void set_a(const int& b);
  void calculate_hash();

 private:
  int a;
};

#endif  // MULTITHREADS_HASH_CALCULATOR_HPP
