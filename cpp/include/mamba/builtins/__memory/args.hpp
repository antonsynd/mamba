#pragma once

#include <memory>
#include <type_traits>

#include "mamba/builtins/__concepts/value.hpp"
#include "mamba/builtins/__memory/ref.hpp"

namespace mamba::builtins {
namespace __memory {

/// @brief For use in return values.
template <typename T>
using Ret = std::conditional_t<__concepts::Value<T>, std::decay_t<T>, Ref<T>>;

/// @brief Alias for use in storing (mutable) values.
template <typename T>
using Stored = Ret<T>;

/// @brief For use in constant arguments.
template <typename T>
using Const = std::
    conditional_t<__concepts::Value<T>, const std::decay_t<T>, const Ref<T>&>;

/// @brief For use in mutable arguments.
/// @note Ref<T> is passed as an lvalue ref to avoid unnecessary copying. The
/// callee can always copy it internally anyway.
template <typename T>
using Mut =
    std::conditional_t<__concepts::Value<T>, const std::decay_t<T>, Ref<T>&>;

}  // namespace __memory

namespace __concepts {

template <typename T>
concept IsArg =
    std::same_as<std::decay_t<T>, __memory::Ret<__memory::Unwrap<T>>>;

}  // namespace __concepts
}  // namespace mamba::builtins

// IWYU pragma: private
