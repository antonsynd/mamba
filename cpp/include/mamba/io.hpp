#pragma once
#include <iostream>

#include "mamba/string.hpp"

namespace mamba {

template <typename... Args>
void print(String s) {
  std::cout << s.GetValue() << std::endl;
}

}  // namespace mamba
