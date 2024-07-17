#pragma once
#include <iostream>

#include "mamba/string.hpp"

namespace mamba {

void print(String s) {
  std::cout << s.GetValue() << std::endl;
}

}  // namespace mamba
