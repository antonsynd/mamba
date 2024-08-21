#pragma once

#include "mamba/concepts/handle.hpp"
#include "mamba/concepts/value.hpp"

namespace mamba::builtins::concepts {

/// @brief Concept for all things that can be operated on and stored, e.g.
/// handles of objects or pure values.
template <typename T>
concept Entity = Handle<T> || Value<T>;

}  // namespace mamba::builtins::concepts
