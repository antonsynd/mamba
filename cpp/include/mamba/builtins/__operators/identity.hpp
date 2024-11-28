#pragma once

#include "mamba/builtins/__concepts/value.hpp"
#include "mamba/builtins/__memory/const.hpp"
#include "mamba/builtins/__types/bool.hpp"
#include "mamba/builtins/__types/none.hpp"

namespace mamba::builtins::__operators {

// Values are compared directly by value
template <__concepts::Value T>
__types::Bool Is(const T& lhs, const T& rhs) {
  return lhs == rhs;
}

// Objects are compared by memory address
template <typename T>
__types::Bool Is(__memory::Const<T> lhs, __memory::Const<T> rhs) {
  return lhs == rhs;
}

// Specialization for None type
template <typename T>
__types::Bool Is(__memory::Const<T>, __types::None) {
  return false;
}

template <typename T>
__types::Bool Is(__types::None, __memory::Const<T>) {
  return false;
}

}  // namespace mamba::builtins::__operators

// IWYU pragma: private
