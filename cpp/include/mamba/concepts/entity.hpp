#pragma once

#include "mamba/concepts/object.hpp"
#include "mamba/concepts/value.hpp"

namespace mamba::builtins::concepts {

/// @brief Concept for objects or pure values.
template <typename T>
concept Entity = Object<T> || Value<T>;

}  // namespace mamba::builtins::concepts
