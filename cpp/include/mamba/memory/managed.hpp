#pragma once

#include <type_traits>

#include "mamba/concepts/entity.hpp"
#include "mamba/concepts/object.hpp"
#include "mamba/concepts/value.hpp"
#include "mamba/memory/handle.hpp"

namespace mamba::builtins::memory {

/// @brief Template for actual container storage elements to properly store
/// objects as managed handles, and values as raw values.
template <concepts::Entity T>
using managed_t =
    std::conditional_t<concepts::Object<T>,
                       handle_t<T>,
                       std::conditional_t<concepts::Value<T>, T, void>>;

/// @brief Concept for value types or managed objects. Used as for variables,
/// members, function arguments, and actual container storage elements (but
/// not the raw template element type itself).
template <typename T>
concept Managed = Handle<T> || concepts::Value<T>;

}  // namespace mamba::builtins::memory
