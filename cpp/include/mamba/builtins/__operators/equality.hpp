#pragma once

#include <utility>

#include "mamba/builtins/__concepts/equatable.hpp"
#include "mamba/builtins/__concepts/object_like.hpp"
#include "mamba/builtins/__types/bool.hpp"

// Generic overload invoking __Eq__() dunder method
template <mamba::builtins::__concepts::EquatableObject T>
bool operator==(const T& lhs, const T& rhs) {
  return lhs.__Eq__(rhs);
}

// If T doesn't have __Eq__(), then equality means identity
template <mamba::builtins::__concepts::ObjectLike T>
bool operator==(const T& lhs, const T& rhs) {
  return lhs.__Id__() == rhs.__Id__();
}

// Specialization of != if __Ne__() is defined
template <mamba::builtins::__concepts::InequatableObject T>
bool operator!=(const T& lhs, const T& rhs) {
  return lhs.__Ne__(rhs);
}

// Fallback to inverse of == if __Ne__() is not defined
template <typename T>
bool operator!=(const T& lhs, const T& rhs) {
  return !(lhs == rhs);
}

// IWYU pragma: private
