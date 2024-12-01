#pragma once

#include <concepts>
#include <memory>
#include <type_traits>

#include "mamba/builtins/__concepts/value.hpp"

namespace mamba::builtins {
namespace __memory {

/// @brief Alias for a type T that is always a one-level shared_ptr (disallows
/// nesting).
template <typename T>
using Ref = std::shared_ptr<T>;

}  // namespace __memory

namespace __concepts {

template <typename T>
concept HasElementType = requires { typename T::element_type; };

template <typename T>
concept IsRef =
    HasElementType<T> &&
    std::same_as<std::decay_t<T>, __memory::Ref<typename T::element_type>>;

}  // namespace __concepts

namespace __memory {

/// @brief Unwraps Ref<T> to T, otherwise just T.
template <typename T>
using UnwrapRef = std::conditional_t<__concepts::IsRef<T>,
                                     typename T::element_type,
                                     std::decay_t<T>>;

/// @brief Unwraps a type T from a Ref<T> if it is one, otherwise just T.
template <typename T>
using Unwrap =
    std::conditional_t<__concepts::Value<T>, std::decay_t<T>, UnwrapRef<T>>;

}  // namespace __memory
}  // namespace mamba::builtins

// IWYU pragma: private
