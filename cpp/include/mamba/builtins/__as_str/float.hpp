#pragma once

#include <string>

#include "mamba/builtins/__types/float.hpp"
#include "mamba/builtins/__types/str.hpp"

namespace mamba::builtins {

inline __types::Str AsStr(__types::Float f) {
  return std::to_string(f);
}

}  // namespace mamba::builtins

// IWYU pragma: private
