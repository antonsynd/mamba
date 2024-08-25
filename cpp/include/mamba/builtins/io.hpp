#pragma once

#include <iostream>

#include "mamba/builtins/as_str.hpp"

namespace mamba::builtins {

template <typename... Args>
void print(Args&&... args) {
  std::cout << AsStr(args) << &&...;
  std::cout << std::endl;
}

}  // namespace mamba::builtins
