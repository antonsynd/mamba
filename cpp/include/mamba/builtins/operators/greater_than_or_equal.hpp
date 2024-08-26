#pragma once

#include "mamba/builtins/__types/bool.hpp"
#include "mamba/builtins/operators/equality.hpp"
#include "mamba/builtins/operators/greater_than.hpp"

namespace mamba::builtins::operators {

template <typename T, typename U>
__types::Bool GtEq(T&& t, U&& u) {
  return Gt(std::forward<T>(t), std::forward<U>(u)) ||
         Eq(std::forward<T>(t), std::forward<U>(u));
}

// C++ operator
template <typename T, typename U>
bool operator>=(T&& t, U&& u) {
  return GtEq(std::forward<T>(t), std::forward<U>(u));
}

}  // namespace mamba::builtins::operators
