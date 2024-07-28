#pragma once

#include "mamba/bool.hpp"

namespace mamba::builtins::comparison {

template <typename T, typename U>
types::Bool Eq(const T& lhs, const U& rhs) {
  return lhs.Eq(rhs);
}

}  // namespace mamba::builtins::comparison
