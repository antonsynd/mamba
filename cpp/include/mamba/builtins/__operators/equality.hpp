#pragma once

#include <utility>

#include "mamba/builtins/__concepts/equatable.hpp"
#include "mamba/builtins/__types/bool.hpp"

// Generic overloads invoking __Eq__() dunder method
template <mamba::builtins::__concepts::EquatableObject T>
bool operator==(const T& lhs, const T& rhs) {
  return lhs.__Eq__(rhs);
}

// Specialization of != if __Ne__() is defined
template <mamba::builtins::__concepts::InequatableObject T>
bool operator!=(const T& lhs, const T& rhs) {
  return lhs.__Ne__(rhs);
}

// Fallback to inverse of == if __Ne__() is not defined but __Eq__() is
template <mamba::builtins::__concepts::EquatableObject T>
bool operator!=(const T& lhs, const T& rhs) {
  return !(lhs == rhs);
}

// IWYU pragma: private
