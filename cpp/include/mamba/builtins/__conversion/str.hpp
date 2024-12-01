#pragma once

#include "mamba/builtins/__dunder/__str/bool.hpp"   // IWYU pragma: export
#include "mamba/builtins/__dunder/__str/float.hpp"  // IWYU pragma: export
#include "mamba/builtins/__dunder/__str/int.hpp"    // IWYU pragma: export
#include "mamba/builtins/__dunder/__str/none.hpp"   // IWYU pragma: export
#include "mamba/builtins/__dunder/__str/str.hpp"    // IWYU pragma: export
#include "mamba/builtins/__dunder/__str/tuple.hpp"  // IWYU pragma: export
#include "mamba/builtins/__memory/args.hpp"
#include "mamba/builtins/__types/str.hpp"

namespace mamba::builtins::__conversion {

template <typename T>
__types::Str Str(__memory::Const<T> t) {
  return t->__Str__();
}

}  // namespace mamba::builtins::__conversion
