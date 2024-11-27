#pragma once

#include "mamba/builtins/__concepts/value.hpp"
#include "mamba/builtins/__memory/ref.hpp"

namespace mamba::builtins::__memory {

/// @brief Template for raw object or value types for use in function arguments
/// to only accept managed handles of objects, and the raw values otherwise.
template <typename T>
using Const = std::conditional_t<__concepts::Value<T>, const T, const Ref<T>&>;

}  // namespace mamba::builtins::__memory

// IWYU pragma: private
