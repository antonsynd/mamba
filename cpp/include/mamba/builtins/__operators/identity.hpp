#pragma once

#include "mamba/builtins/__meta/types.hpp"
#include "mamba/builtins/__types/none.hpp"

namespace mamba::builtins {

/// @overload
/// @brief Returns `true `Values are identical if they have the same value, and
/// references are identical if their pointers are the same.
template <typename T>
bool Is(const T& lhs, const T& rhs) {
  return lhs == rhs;
}

/// @overload
/// @brief Specialization for None type, only None is identical to None
template <details::Optional T>
bool Is(const T& lhs, details::None) {
  return !lhs;
}

template <details::Optional T>
bool Is(details::None, const T& rhs) {
  return !rhs;
}

bool Is(details::None, details::None) {
  return true;
}

}  // namespace mamba::builtins

// IWYU pragma: private
