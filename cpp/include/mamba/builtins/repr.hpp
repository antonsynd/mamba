#pragma once

#include "mamba/builtins/__dunder/__repr/bool.hpp"   // IWYU pragma: export
#include "mamba/builtins/__dunder/__repr/float.hpp"  // IWYU pragma: export
#include "mamba/builtins/__dunder/__repr/int.hpp"    // IWYU pragma: export
#include "mamba/builtins/__dunder/__repr/none.hpp"   // IWYU pragma: export
#include "mamba/builtins/__dunder/__repr/str.hpp"    // IWYU pragma: export
#include "mamba/builtins/__dunder/__repr/tuple.hpp"  // IWYU pragma: export
#include "mamba/builtins/__memory/const.hpp"
#include "mamba/builtins/__types/str.hpp"

namespace mamba::builtins {

template <typename T>
__types::Str Repr(__memory::Const<T> t) {
  return t->__Repr__();
}

}  // namespace mamba::builtins
