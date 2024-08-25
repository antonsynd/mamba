#pragma once

#include "mamba/concepts/bool_convertible.hpp"
#include "mamba/concepts/str_convertible.hpp"
#include "mamba/memory/handle.hpp"
#include "mamba/types/bool.hpp"
#include "mamba/types/str.hpp"

namespace mamba::builtins {

template <concepts::BoolConvertibleObject T>
types::Bool AsBool(const memory::handle_t<T>& t) {
  return t->AsBool();
}

template <concepts::StrConvertibleObject T>
types::Str AsStr(const memory::handle_t<T>& t) {
  return t->AsStr();
}

template <concepts::Object T>
types::Str Repr(const memory::handle_t<T>& t) {
  return t->Repr();
}

// For unit testing
template <concepts::BoolConvertibleObject T>
types::Bool AsBool(const T& t) {
  return t.AsBool();
}

template <concepts::StrConvertibleObject T>
types::Str AsStr(const T& t) {
  return t.AsStr();
}

template <concepts::Object T>
types::Str Repr(const T& t) {
  return t.Repr();
}

}  // namespace mamba::builtins
