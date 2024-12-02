#pragma once

#include <memory>
#include <type_traits>

#include "mamba/builtins/__concepts/value.hpp"

namespace mamba::builtins::__memory {

/// @brief For use in constant arguments.
template <typename T>
using Const = std::conditional_t<__concepts::Value<T>, const T, const T&>;

/// @brief For use in mutable arguments.
/// @note Ref<T> is passed as an lvalue ref to avoid unnecessary copying. The
/// callee can always copy it internally anyway.
template <typename T>
using Mut = std::conditional_t<__concepts::Value<T>, const T, T&>;

}  // namespace mamba::builtins::__memory

// IWYU pragma: private
