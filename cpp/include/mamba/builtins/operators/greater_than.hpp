#pragma once

#include "mamba/builtins/__memory/const.hpp"
#include "mamba/builtins/__types/bool.hpp"

template <typename T>
bool operator>(mamba::builtins::__memory::Const<T> lhs,
               mamba::builtins::__memory::Const<T> rhs) {
  return lhs->__Gt__(rhs);
}

// IWYU pragma: private
