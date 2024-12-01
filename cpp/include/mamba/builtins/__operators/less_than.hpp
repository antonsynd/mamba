#pragma once

#include "mamba/builtins/__memory/args.hpp"
#include "mamba/builtins/__types/bool.hpp"

template <typename T>
bool operator<(mamba::builtins::__memory::Const<T> lhs,
               mamba::builtins::__memory::Const<T> rhs) {
  return lhs->__Lt__(rhs);
}

// IWYU pragma: private
