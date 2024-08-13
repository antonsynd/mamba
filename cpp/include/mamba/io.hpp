#pragma once

#include <iostream>

#include "mamba/conversion.hpp"

namespace mamba::builtins {

template <typename... Args>
void print(Args&&... args) {
  std::cout << Str(args) << &&...;
  std::cout << std::endl;
}

}  // namespace mamba::builtins
