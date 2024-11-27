#pragma once

#include "mamba/builtins/__types/bool.hpp"

namespace mamba::builtins::__conversion {

inline __types::Bool Bool(__types::Bool b) {
  return b;
}

}  // namespace mamba::builtins::__conversion

// IWYU pragma: private
