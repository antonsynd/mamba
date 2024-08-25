#pragma once

#include "mamba/builtins/__types/none.hpp"
#include "mamba/builtins/__types/str.hpp"

namespace mamba::builtins {

inline __types::Str AsStr(__types::None) {
  return "None";
}

}  // namespace mamba::builtins
