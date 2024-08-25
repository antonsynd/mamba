#pragma once

#include "mamba/builtins/__types/bool.hpp"
#include "mamba/builtins/__types/int.hpp"

namespace mamba::builtins {

inline __types::Bool AsBool(__types::Int i) {
  return i != 0;
}

}  // namespace mamba::builtins
