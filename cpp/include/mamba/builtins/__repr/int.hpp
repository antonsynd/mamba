#pragma once

#include <string>

#include "mamba/builtins/__types/int.hpp"
#include "mamba/builtins/__types/str.hpp"

namespace mamba::builtins {

inline __types::Str Repr(__types::Int i) {
  return std::to_string(i);
}

}  // namespace mamba::builtins

// IWYU pragma: private
