#pragma once

#include "mamba/object.hpp"
#include "mamba/value.hpp"

namespace mamba::builtins::concepts {

template <typename T>
concept Entity = Object<T> || Value<T>;

}  // namespace mamba::builtins::concepts
