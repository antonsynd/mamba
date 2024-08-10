#pragma once

#include "mamba/reference.hpp"
#include "mamba/value.hpp"

namespace mamba::builtins::concepts {

template <typename T>
concept Entity = Reference<T> || Value<T>;

}  // namespace mamba::builtins::concepts
