#pragma once

#include <memory>
#include <type_traits>

#include "mamba/builtins/__concepts/value.hpp"
#include "mamba/builtins/__memory/ref.hpp"

namespace mamba::builtins::__memory {

template <typename T>
using Entity = std::conditional_t<__concepts::Value<T>, T, Ref<T>>;

}  // namespace mamba::builtins::__memory

// IWYU pragma: private
