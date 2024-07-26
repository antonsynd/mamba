#pragma once

#include <concepts>
#include <type_traits>
#include <utility>

#include "mamba/bool.hpp"
#include "mamba/concepts.hpp"
#include "mamba/float.hpp"
#include "mamba/int.hpp"
#include "mamba/str.hpp"

namespace mamba::builtins {

Bool as_bool(Bool b) {
  return b;
}

Bool as_bool(Int i) {
  return i != 0;
}

Bool as_bool(Float f) {
  return f != 0;
}

Bool as_bool(Str s) {
  return !s.empty();
}

template <BoolConvertible T>
Bool as_bool(const T& t) {
  return t.as_bool();
}

Str as_str(Int i) {
  return std::to_string(i);
}

Str as_str(Float f) {
  return std::to_string(f);
}

Str as_str(Bool f) {
  return std::to_string(f);
}

/// @note The return value is expected to be a new copy of @p s. Returning an
/// lvalue ref is not expected here. However, we can move a temporary if it
/// was passed in, hence the use of a forwarding reference.
Str as_str(Str&& s) {
  return std::forward<Str>(s);
}

template <concepts::StrConvertible T>
Bool as_str(const T& t) {
  return T.as_str();
}

}  // namespace mamba::builtins
