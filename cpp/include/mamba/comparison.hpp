#pragma once

#include "mamba/bool.hpp"

namespace mamba::builtins::comparison {

template <typename T, typename U>
types::Bool Eq(const T& lhs, const U& rhs) {
  return lhs.Eq(rhs);
}

template <typename T, typename U>
types::Bool StrictEq(const T& lhs, const U& rhs) {
  return lhs.StrictEq(rhs);
}

// For C++ syntax
template <typename T, typename U>
bool operator==(const T& lhs, const U& rhs) {
  return lhs == rhs;
}

template <typename T, typename U>
bool operator!=(const T& lhs, const U& rhs) {
  return !(operator==(lhs, rhs));
}

}  // namespace mamba::builtins::comparison
