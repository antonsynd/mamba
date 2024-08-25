#pragma once

#include "mamba/builtins/__types/bool.hpp"
#include "mamba/builtins/__types/none.hpp"

namespace mamba::builtins {

inline __types::Bool AsBool(__types::None) {
  return false;
}

}  // namespace mamba::builtins
