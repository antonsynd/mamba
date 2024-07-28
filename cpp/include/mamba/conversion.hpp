#pragma once

#include <concepts>
#include <type_traits>
#include <utility>

#include "mamba/bool.hpp"
#include "mamba/concepts.hpp"
#include "mamba/float.hpp"
#include "mamba/int.hpp"
#include "mamba/str.hpp"

namespace mamba::builtins::conversion {

// TODO: Add overload for Bool if necessary
types::Bool Bool(types::Int i) {
  return i != 0;
}

types::Bool Bool(types::Float f) {
  return f != 0;
}

types::Bool Bool(types::Str s) {
  return !s.empty();
}

template <concepts::BoolConvertible T>
types::Bool Bool(const T& t) {
  return t.AsBool();
}

// TODO: Add overload for Bool if necessary
types::Str Str(types::Int i) {
  return std::to_string(i);
}

types::Str Str(types::Float f) {
  return std::to_string(f);
}

/// @note The return value is expected to be a new copy of @p s. Returning an
/// lvalue ref is not expected here. However, we can move a temporary if it
/// was passed in, hence the use of a forwarding reference.
types::Str Str(types::Str&& s) {
  return std::forward<types::Str>(s);
}

template <concepts::StrConvertible T>
types::Bool Str(const T& t) {
  return t.AsStr();
}

}  // namespace mamba::builtins::conversion
