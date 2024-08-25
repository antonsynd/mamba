#pragma once

#include "mamba/concepts/entity.hpp"
#include "mamba/concepts/object.hpp"
#include "mamba/concepts/value.hpp"
#include "mamba/memory/handle.hpp"

namespace mamba::builtins::memory {

/// @brief Template for raw object or value types for use in function arguments
/// to only accept managed handles of objects, and the raw values otherwise.
template <concepts::Entity T>
using ReadOnly =
    std::conditional_t<concepts::Object<T>,
                       const handle_t<T>&,
                       std::conditional_t<concepts::Value<T>, T, void>>;

}  // namespace mamba::builtins::memory
