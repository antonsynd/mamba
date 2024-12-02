#pragma once

#include <iostream>

#include "mamba/builtins/conversion/str.hpp"

namespace mamba::builtins {

template <typename... Args>
void print(Args&&... args) {
  std::cout << conversion::Str(args) << &&...;
  std::cout << std::endl;
}

}  // namespace mamba::builtins
