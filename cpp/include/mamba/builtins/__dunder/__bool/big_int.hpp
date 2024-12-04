#pragma once

#include "mamba/builtins/__types/big_int.hpp"
#include "mamba/builtins/__types/bool.hpp"

namespace mamba::builtins::__conversion {

inline __types::Bool Bool(__types::BigInt i) {
  return i != 0;
}

}  // namespace mamba::builtins::__conversion

// IWYU pragma: private
