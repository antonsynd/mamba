#pragma once

#include "mamba/builtins/__types/none.hpp"
#include "mamba/builtins/__types/str.hpp"

namespace mamba::builtins::__conversion {

template <typename T>
inline __types::Str Str(__types::None<T>) {
  return "None";
}

}  // namespace mamba::builtins::__conversion

// IWYU pragma: private
