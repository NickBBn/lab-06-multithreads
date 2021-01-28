//
// Created by nickmint on 1/26/21.
//

#include "hash_calculator.hpp"
int hash_calculator::get_a() const { return a; }

void hash_calculator::set_a(const int& b) { a = b; }

void hash_calculator::calculate_hash() {
  std::cout << "id from calculator: " << std::this_thread::get_id() << std::endl;
}
