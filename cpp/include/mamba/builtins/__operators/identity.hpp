#pragma once

#include "mamba/builtins/__concepts/value.hpp"
#include "mamba/builtins/__memory/args.hpp"
#include "mamba/builtins/__types/bool.hpp"
#include "mamba/builtins/__types/none.hpp"

namespace mamba::builtins::__operators::identity {

// Values are identical if they have the same value
template <__concepts::Value T>
__types::Bool Is(const T lhs, const T rhs) {
  return lhs == rhs;
}

// Non-values are identical if they have the same id (implementation detail:
// which is their memory address)
template <__concepts::NotValue T>
__types::Bool Is(const T& lhs, const T& rhs) {
  return lhs.__Id__() == rhs.__Id__();
}

// Specialization for None type, only None is identical to None
template <typename T>
__types::Bool Is(__memory::Const<T>, __types::None) {
  return false;
}

template <typename T>
__types::Bool Is(__types::None, __memory::Const<T>) {
  return false;
}

__types::Bool Is(__types::None, __types::None) {
  return true;
}

}  // namespace mamba::builtins::__operators::identity

// IWYU pragma: private
