#pragma once

#include <memory>
#include <type_traits>

#include "mamba/builtins/__concepts/value.hpp"

namespace mamba::builtins::__memory {

/// @brief For use in constant arguments.
template <typename T>
using Const = std::conditional_t<__concepts::Value<T>, const T, const T&>;

/// @brief For use in mutable arguments.
/// @note Non-values are passed as lvalue refs to avoid unnecessary copying. The
/// callee can always copy it internally anyway.
template <typename T>
using Mut = std::conditional_t<__concepts::Value<T>, const T, T&>;

/// @brief For use in mutable arguments where the callee must be owned.
/// @note Non-values are passed as rvalue refs.
template <typename T>
using Own = std::conditional_t<__concepts::Value<T>, const T, T&&>;

/// @brief Specialization for "Move" that should result in no overhead for
/// values.
template <__concepts::Value T>
auto Move(T&& t) {
  return t;
}

/// @brief Specialiation for "Move" that should result in the movement of the
/// argument.
template <__concepts::NotValue T>
auto Move(T&& t) {
  return std::move(std::forward<T>(t));
}

}  // namespace mamba::builtins::__memory

// IWYU pragma: private
