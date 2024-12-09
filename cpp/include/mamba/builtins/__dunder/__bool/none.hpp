#pragma once

#include "mamba/builtins/__types/bool.hpp"
#include "mamba/builtins/__types/none.hpp"

namespace mamba::builtins::__conversion {

inline __types::Bool Bool(__types::None) {
  return false;
}

}  // namespace mamba::builtins::__conversion

// IWYU pragma: private
