#pragma once

#include "mamba/builtins/__types/bool.hpp"
#include "mamba/builtins/__types/str.hpp"

namespace mamba::builtins::__conversion {

inline __types::Str Str(__types::Bool b) {
  return b ? "True" : "False";
}

}  // namespace mamba::builtins::__conversion

// IWYU pragma: private
