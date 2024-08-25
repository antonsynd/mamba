#pragma once

#include "mamba/__concepts/object.hpp"
#include "mamba/__memory/handle.hpp"
#include "mamba/builtins/__repr/bool.hpp"   // IWYU pragma: export
#include "mamba/builtins/__repr/float.hpp"  // IWYU pragma: export
#include "mamba/builtins/__repr/int.hpp"    // IWYU pragma: export
#include "mamba/builtins/__repr/none.hpp"   // IWYU pragma: export
#include "mamba/builtins/__repr/str.hpp"    // IWYU pragma: export
#include "mamba/builtins/__repr/tuple.hpp"  // IWYU pragma: export
#include "mamba/builtins/__types/str.hpp"

namespace mamba::builtins {

template <__concepts::Object T>
__types::Str Repr(const T& t) {
  return t.Repr();
}

template <__concepts::Object T>
__types::Str Repr(const __memory::handle_t<T>& t) {
  return Repr(*t);
}

}  // namespace mamba::builtins
