#pragma once

#include "mamba/value.hpp"

namespace mamba::builtins::concepts {

template <typename T>
concept Object = !Value<T>;

}  // namespace mamba::builtins::concepts
