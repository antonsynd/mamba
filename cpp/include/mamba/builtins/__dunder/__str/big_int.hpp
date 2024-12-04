#pragma once

#include <string>

#include "mamba/builtins/__types/big_int.hpp"
#include "mamba/builtins/__types/str.hpp"

namespace mamba::builtins {

inline __types::Str Str(__types::BigInt i) {
  return std::to_string(i);
}

}  // namespace mamba::builtins

// IWYU pragma: private
