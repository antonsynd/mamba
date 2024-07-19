#pragma once
#include <iostream>

#include "mamba/alpha/string.hpp"

namespace mamba {

template <typename... Args>
void print(String s) {
  std::cout << s.GetValue() << std::endl;
}

}  // namespace mamba
