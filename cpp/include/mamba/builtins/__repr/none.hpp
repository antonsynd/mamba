#pragma once

#include "mamba/builtins/__types/none.hpp"
#include "mamba/builtins/__types/str.hpp"

namespace mamba::builtins {

inline __types::Str Repr(__types::None) {
  return "None";
}

}  // namespace mamba::builtins

// IWYU pragma: private
