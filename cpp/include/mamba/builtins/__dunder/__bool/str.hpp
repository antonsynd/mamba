#pragma once

#include "mamba/builtins/__types/bool.hpp"
#include "mamba/builtins/__types/str.hpp"

namespace mamba::builtins::__conversion {

inline __types::Bool Bool(__types::Str s) {
  return !s.empty();
}

}  // namespace mamba::builtins::__conversion

// IWYU pragma: private
