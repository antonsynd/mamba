#pragma once

#include "mamba/builtins/__types/bool.hpp"
#include "mamba/builtins/__types/str.hpp"

namespace mamba::builtins {

inline __types::Bool AsBool(__types::Str s) {
  return !s.empty();
}

}  // namespace mamba::builtins

// IWYU pragma: private
