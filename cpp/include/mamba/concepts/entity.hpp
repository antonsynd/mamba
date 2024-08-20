#pragma once

#include "mamba/concepts/handle.hpp"
#include "mamba/concepts/value.hpp"

namespace mamba::builtins::concepts {

template <typename T>
concept Entity = Handle<T> || Value<T>;

}  // namespace mamba::builtins::concepts
