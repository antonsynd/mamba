#pragma once

#include "mamba/builtins/__types/none.hpp"
#include "mamba/builtins/__types/str.hpp"

namespace mamba::builtins {

template <typename T>
inline __types::Str AsStr(__types::None<T>) {
  return "None";
}

}  // namespace mamba::builtins

// IWYU pragma: private
