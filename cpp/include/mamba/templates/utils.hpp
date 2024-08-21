#pragma once

#include "mamba/concepts/entity.hpp"
#include "mamba/concepts/handle.hpp"
#include "mamba/concepts/value.hpp"

namespace mamba::builtins::templates {

template <concepts::Entity T>
using Lvalue =
    std::conditional_t<concepts::Handle<T>,
                       const memory::Handle<T::element_type>&,
                       std::conditional_t<concepts::Value<T>, T, void>>;

}  // namespace mamba::builtins::templates
