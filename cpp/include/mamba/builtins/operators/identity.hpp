#pragma once

#include "mamba/builtins/__concepts/value.hpp"
#include "mamba/builtins/__memory/const.hpp"
#include "mamba/builtins/__types/bool.hpp"

namespace mamba::builtins::operators {

/// Values are compared directly by value
template <__concepts::Value T>
__types::Bool Is(const T& lhs, const T& rhs) {
  return lhs == rhs;
}

/// Objects are compared by memory address
template <typename T>
__types::Bool Is(mamba::builtins::__memory::Const<T> lhs,
                 mamba::builtins::__memory::Const<T> rhs) {
  return lhs == rhs;
}

// Specialization for None type
template <typename T, typename U = T>
__types::Bool Is(mamba::builtins::__memory::Const<T>,
                 mamba::builtins::__types::None<U>) {
  return false;
}

template <typename T, typename U = T>
__types::Bool Is(mamba::builtins::__types::None<U>,
                 mamba::builtins::__memory::Const<T>) {
  return false;
}

}  // namespace mamba::builtins::operators

// IWYU pragma: private
