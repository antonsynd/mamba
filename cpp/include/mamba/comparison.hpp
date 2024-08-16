#pragma once

#include <concepts>

#include "mamba/concepts/object.hpp"
#include "mamba/types/bool.hpp"

namespace mamba::builtins {
namespace operators {

template <concepts::EquatableObject T, concepts::EquatableObject U>
types::Bool Eq(const T& lhs, const U& rhs) {
  return lhs.Eq(rhs);
}

template <concepts::LessThanComparableObject T,
          concepts::LessThanComparableObject U>
types::Bool Lt(const T& lhs, const U& rhs) {
  return lhs.Lt(rhs);
}

template <concepts::GreaterThanComparableObject T,
          concepts::GreaterThanComparableObject U>
types::Bool Gt(const T& lhs, const U& rhs) {
  return lhs.Gt(rhs);
}

}  // namespace operators

// For C++ syntax
template <concepts::EquatableObject T, concepts::EquatableObject U>
bool operator==(const T& lhs, const U& rhs) {
  return lhs.Eq(rhs);
}

template <concepts::EquatableObject T, concepts::EquatableObject U>
bool operator!=(const T& lhs, const U& rhs) {
  return !(operator==(lhs, rhs));
}

template <concepts::LessThanComparableObject T,
          concepts::LessThanComparableObject U>
bool operator<(const T& lhs, const U& rhs) {
  return lhs.Lt(rhs);
}

template <concepts::GreaterThanComparableObject T,
          concepts::GreaterThanComparableObject U>
bool operator>(const T& lhs, const U& rhs) {
  return lhs.Gt(rhs);
}

}  // namespace mamba::builtins
