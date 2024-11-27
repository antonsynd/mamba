#pragma once

#include "mamba/builtins/__dunder/__bool/bool.hpp"   // IWYU pragma: export
#include "mamba/builtins/__dunder/__bool/float.hpp"  // IWYU pragma: export
#include "mamba/builtins/__dunder/__bool/int.hpp"    // IWYU pragma: export
#include "mamba/builtins/__dunder/__bool/none.hpp"   // IWYU pragma: export
#include "mamba/builtins/__dunder/__bool/str.hpp"    // IWYU pragma: export
#include "mamba/builtins/__dunder/__bool/tuple.hpp"  // IWYU pragma: export
#include "mamba/builtins/__memory/ref.hpp"
#include "mamba/builtins/__types/bool.hpp"

namespace mamba::builtins::conversion {

template <typename T>
__types::Bool Bool(const T& t) {
  return t->__Bool__();
}

template <typename T>
__types::Bool Bool(const __memory::Ref<T>& t) {
  return Bool(*t);
}

}  // namespace mamba::builtins::conversion
