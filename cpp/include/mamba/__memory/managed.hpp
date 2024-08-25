#pragma once

#include <type_traits>

#include "mamba/__concepts/entity.hpp"
#include "mamba/__concepts/object.hpp"
#include "mamba/__concepts/value.hpp"
#include "mamba/__memory/handle.hpp"

namespace mamba::builtins::__memory {

/// @brief Template for actual container storage elements to properly store
/// objects as managed handles, and values as raw values.
template <__concepts::Entity T>
using managed_t =
    std::conditional_t<__concepts::Object<T>,
                       handle_t<T>,
                       std::conditional_t<__concepts::Value<T>, T, void>>;

/// @brief Concept for value types or managed objects. Used as for variables,
/// members, function arguments, and actual container storage elements (but
/// not the raw template element type itself).
template <typename T>
concept Managed = Handle<T> || __concepts::Value<T>;

}  // namespace mamba::builtins::__memory
