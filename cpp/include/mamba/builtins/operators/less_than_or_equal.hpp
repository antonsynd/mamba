#pragma once

#include "mamba/builtins/__types/bool.hpp"
#include "mamba/builtins/operators/equality.hpp"
#include "mamba/builtins/operators/less_than.hpp"

namespace mamba::builtins::operators {

template <typename T, typename U>
__types::Bool LtEq(T&& t, U&& u) {
  return Lt(std::forward<T>(t), std::forward<U>(u)) ||
         Eq(std::forward<T>(t), std::forward<U>(u));
}

// C++ operator
template <typename T, typename U>
bool operator<=(T&& t, U&& u) {
  return LtEq(std::forward<T>(t), std::forward<U>(u));
}

}  // namespace mamba::builtins::operators
