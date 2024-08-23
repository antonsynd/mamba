#pragma once

#include <type_traits>

#include "mamba/concepts/entity.hpp"
#include "mamba/concepts/object.hpp"
#include "mamba/concepts/value.hpp"
#include "mamba/memory/handle.hpp"

namespace mamba::builtins::memory {

template <concepts::Entity T>
using managed_t =
    std::conditional_t<concepts::Object<T>,
                       handle_t<T>,
                       std::conditional_t<concepts::Value<T>, T, void>>;

template <typename T>
concept Managed = Handle<T> || concepts::Value<T>;

}  // namespace mamba::builtins::memory
