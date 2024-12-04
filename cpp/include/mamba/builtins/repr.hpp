#pragma once

#include "mamba/builtins/__concepts/value.hpp"
#include "mamba/builtins/__dunder/__repr/big_int.hpp"  // IWYU pragma: export
#include "mamba/builtins/__dunder/__repr/bool.hpp"     // IWYU pragma: export
#include "mamba/builtins/__dunder/__repr/float.hpp"    // IWYU pragma: export
#include "mamba/builtins/__dunder/__repr/int.hpp"      // IWYU pragma: export
#include "mamba/builtins/__dunder/__repr/none.hpp"     // IWYU pragma: export
#include "mamba/builtins/__dunder/__repr/tuple.hpp"    // IWYU pragma: export
#include "mamba/builtins/__types/str.hpp"

namespace mamba::builtins {

template <__concepts::NotValue T>
__types::Str Repr(const T& t) {
  return t.__Repr__();
}

}  // namespace mamba::builtins
