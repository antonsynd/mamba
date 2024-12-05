#pragma once

#include <string>

#include "mamba/builtins/__types/int.hpp"
#include "mamba/builtins/__types/str.hpp"

namespace mamba::builtins::__conversion {

inline __types::Str Str(__types::Int i) {
  return std::to_string(i);
}

}  // namespace mamba::builtins::__conversion

// IWYU pragma: private
