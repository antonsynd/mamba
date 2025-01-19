#pragma once

#include "mamba/builtins/__meta/value.hpp"
#include "mamba/builtins/__meta/wrapped.hpp"
#include "mamba/builtins/__types/none.hpp"

namespace mamba::builtins {

/// @overload
/// @brief For value types, returns `true` if they compare equal. For reference
/// types, returns `true` if they are the same object (via memory address),
/// supporting the raw reference type itself via `operator&()` or via
/// `std::shared_ptr<T>::operator==()`.
///
/// @note There is no second template type param because it doesn't make sense
/// to compare the identity of objects of differing types. For polymorphic
/// reference types, this is handled automatically because their memory
/// addresses would be the same anyway.
template <typename T>
bool Is(const T& lhs, const T& rhs) {
  if constexpr (details::IsValue<T> || details::IsWrapped<T>) {
    return lhs == rhs;
  } else {
    return &lhs == &rhs;
  }
}

/// @overload
/// @brief Specialization for None type, only None is identical to None.
template <details::Optional T>
bool Is(const T& lhs, details::None) {
  return !Unwrap(lhs);
}

/// @overload
/// @brief Specialization for None type, only None is identical to None.
template <details::Optional T>
bool Is(details::None, const T& rhs) {
  return !Unwrap(rhs);
}

/// @overload
/// @brief Specialization for None type, only None is identical to None.
bool Is(details::None, details::None) {
  return true;
}

}  // namespace mamba::builtins

// IWYU pragma: private
