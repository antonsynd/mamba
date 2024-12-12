#pragma once

#include "mamba/builtins/__concepts/orderable.hpp"
#include "mamba/builtins/__types/bool.hpp"

template <mamba::builtins::details::GreaterThanOrEqualComparableObject T>
bool operator>=(const T& lhs, const T& rhs) {
  return lhs.__Ge__(rhs);
}

template <typename T>
  requires mamba::builtins::details::GreaterThanComparableObject<T> &&
           mamba::builtins::details::EquatableObject<T>
bool operator>=(const T& lhs, const T& rhs) {
  return lhs.__Gt__(rhs) || lhs.__Eq__(rhs);
}

// IWYU pragma: private
