#pragma once

#include "mamba/__concepts/entity.hpp"
#include "mamba/__concepts/object.hpp"
#include "mamba/__concepts/value.hpp"
#include "mamba/__memory/handle.hpp"
#include "mamba/__utils/not_null.hpp"

namespace mamba::builtins::__memory {

/// @brief Template for raw object or value types for use in function arguments
/// to only accept managed handles of objects, and the raw values otherwise.
template <__concepts::Entity T>
using ReadOnly =
    std::conditional_t<__concepts::Object<T>,
                       const handle_t<T>&,
                       std::conditional_t<__concepts::Value<T>, T, void>>;

}  // namespace mamba::builtins::__memory

// IWYU pragma: private
