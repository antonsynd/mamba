#pragma once

#include "mamba/builtins/__concepts/orderable.hpp"
#include "mamba/builtins/__types/bool.hpp"

template <mamba::builtins::__concepts::LessThanOrEqualComparable T>
bool operator<=(const T& lhs, const T& rhs) {
  return lhs.__Le__(rhs);
}

template <typename T>
  requires mamba::builtins::__concepts::LessThanComparableObject<T> &&
           mamba::builtins::__concepts::EquatableObject<T>
bool operator<=(const T& lhs, const T& rhs) {
  return lhs.__Lt__(rhs) || lhs.__Eq__(rhs);
}

// IWYU pragma: private
