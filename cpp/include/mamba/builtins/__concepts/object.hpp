#pragma once

#include "mamba/builtins/__concepts/value.hpp"

namespace mamba::builtins::__concepts {

template <typename T>
concept Object = !Value<T>;

}  // namespace mamba::builtins::__concepts

// IWYU pragma: private
