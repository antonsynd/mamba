#pragma once

#include "mamba/__concepts/object.hpp"
#include "mamba/__concepts/value.hpp"

namespace mamba::builtins::__concepts {

/// @brief Concept for objects or pure values. This is for use in templating
/// the main element type of containers.
template <typename T>
concept Entity = Object<T> || Value<T>;

}  // namespace mamba::builtins::__concepts
