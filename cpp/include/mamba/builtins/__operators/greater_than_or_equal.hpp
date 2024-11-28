#pragma once

#include "mamba/builtins/__concepts/comparable.hpp"
#include "mamba/builtins/__memory/const.hpp"
#include "mamba/builtins/__types/bool.hpp"

template <mamba::builtins::__concepts::GreaterThanOrEqualComparable T>
bool operator>=(mamba::builtins::__memory::Const<T> lhs,
                mamba::builtins::__memory::Const<T> rhs) {
  return lhs->__Ge__(rhs);
}

template <typename T>
bool operator>=(mamba::builtins::__memory::Const<T> lhs,
                mamba::builtins::__memory::Const<T> rhs) {
  return lhs->__Gt__(rhs) || lhs->__Eq__(rhs);
}

// IWYU pragma: private
