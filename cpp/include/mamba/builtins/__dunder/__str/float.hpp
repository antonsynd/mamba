#pragma once

#include <string>

#include "mamba/builtins/__types/float.hpp"
#include "mamba/builtins/__types/str.hpp"

namespace mamba::builtins::__conversion {

inline __types::Str Str(__types::Float f) {
  return std::to_string(f);
}

}  // namespace mamba::builtins::__conversion

// IWYU pragma: private
