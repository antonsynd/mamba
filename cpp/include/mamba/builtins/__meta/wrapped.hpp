#pragma once

#include <memory>
#include <type_traits>
#include <utility>

#include "mamba/builtins/__meta/value.hpp"

namespace mamba::builtins::details {

/// @brief All types that should be wrapped in std::shared_ptr<T> are reference
/// types.
template <typename T>
concept IsWrapped = requires {
  typename T::element_type;
} && std::is_same_v<std::decay_t<T>, std::shared_ptr<typename T::element_type>>;

template <typename T>
concept IsNotWrapped = !IsWrapped<T>;

/// @brief Returns the wrapped version of @tparam T for general usage as
/// variable storage or container storage. For types that satisfy
/// @ref IsValue<T>, it returns the type @tparam T itself. For other types,
/// it returns `std::shared_ptr<T>`.
template <typename T>
using Wrapped =
    std::conditional_t<IsValue<T> || IsWrapped<T>, T, std::shared_ptr<T>>;

/// @brief Returns the unwrapped version of @tparam T, as the complement to
/// @ref Wrapped<T>. Generally used to undo @ref Wrapped<T> for @tparam T
/// to obtain the original type, for typing containers in a semantically
/// transparent way.
template <typename T>
using Unwrapped = std::
    conditional_t<IsValue<T> || IsNotWrapped<T>, T, typename T::element_type>;

/// @brief Unwraps @p t from `std::shared_ptr<T>` if it satisfies
/// @ref IsNotValue<T>, otherwise just returns @p t.
template <typename T>
auto Unwrap(T&& t) {
  if constexpr (IsNotWrapped<T>) {
    return std::forward<T>(t);
  } else {
    return std::forward<T::element_type>(*t);
  }
}

/// @brief Wraps @p t into `std::shared_ptr<T>` via `std::move()` if it
/// satisfies @ref IsNotValue<T>, otherwise just returns @p t.
template <typename T>
auto Wrap(T&& t) {
  if constexpr (IsNotWrapped<T>) {
    return std::forward<T>(t);
  } else {
    return std::make_shared<T>(std::move(t));
  }
}

}  // namespace mamba::builtins::details

// IWYU pragma: private
