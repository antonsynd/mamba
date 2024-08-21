#pragma once

#include "mamba/concepts/entity.hpp"
#include "mamba/concepts/handle.hpp"
#include "mamba/concepts/value.hpp"

namespace mamba::builtins::templates {

template <concepts::Entity T>
using ReadOnly =
    std::conditional_t<concepts::Handle<T>,
                       const T&,
                       std::conditional_t<concepts::Value<T>, T, void>>;

template <concepts::Entity T>
using Owned =
    std::conditional_t<concepts::Handle<T>,
                       T&&,
                       std::conditional_t<concepts::Value<T>, T, void>>;

}  // namespace mamba::builtins::templates
