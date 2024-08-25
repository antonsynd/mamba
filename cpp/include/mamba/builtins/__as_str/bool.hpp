#pragma once

#include "mamba/builtins/__types/bool.hpp"
#include "mamba/builtins/__types/str.hpp"

namespace mamba::builtins {

inline __types::Str AsStr(__types::Bool b) {
  return b ? "True" : "False";
}

}  // namespace mamba::builtins
