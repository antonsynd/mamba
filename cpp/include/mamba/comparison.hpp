#pragma once

#include <concepts>

#include "mamba/bool.hpp"

namespace mamba::builtins::operators {

template <typename T, typename U>
types::Bool Eq(const T& lhs, const U& rhs) {
  return lhs.Eq(rhs);
}

template <typename T, typename U>
types::Bool Lt(const T& lhs, const U& rhs) {
  return lhs.Lt(rhs);
}

template <typename T, typename U>
types::Bool Gt(const T& lhs, const U& rhs) {
  return lhs.Gt(rhs);
}

// For C++ syntax
template <typename T, typename U>
bool operator==(const T& lhs, const U& rhs) {
  return lhs.Eq(rhs);
}

template <typename T, typename U>
bool operator!=(const T& lhs, const U& rhs) {
  return !(operator==(lhs, rhs));
}

template <typename T, typename U>
bool operator<(const T& lhs, const U& rhs) {
  return lhs.Lt(rhs);
}

template <typename T, typename U>
bool operator>(const T& lhs, const U& rhs) {
  return lhs.Gt(rhs);
}

namespace concepts {

template <typename T>
concept LessThanComparable = requires(const T t) {
  { t.Lt(t) } -> std::same_as<types::Bool>;
  { t < t } -> std::same_as<types::Bool>;
};

}  // namespace concepts

}  // namespace mamba::builtins::operators
