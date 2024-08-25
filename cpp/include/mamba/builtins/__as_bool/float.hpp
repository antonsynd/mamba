#pragma once

#include "mamba/builtins/__types/bool.hpp"
#include "mamba/builtins/__types/float.hpp"

namespace mamba::builtins {

inline __types::Bool AsBool(__types::Float f) {
  return f != 0.0;
}

}  // namespace mamba::builtins

// IWYU pragma: private
