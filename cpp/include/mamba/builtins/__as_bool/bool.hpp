#pragma once

#include "mamba/builtins/__types/bool.hpp"

namespace mamba::builtins {

inline __types::Bool AsBool(__types::Bool b) {
  return b;
}

}  // namespace mamba::builtins
