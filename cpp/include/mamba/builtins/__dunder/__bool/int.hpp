#pragma once

#include "mamba/builtins/__types/bool.hpp"
#include "mamba/builtins/__types/int.hpp"

namespace mamba::builtins::__conversion {

inline __types::Bool Bool(__types::Int i) {
  return i != 0;
}

}  // namespace mamba::builtins::__conversion

// IWYU pragma: private
