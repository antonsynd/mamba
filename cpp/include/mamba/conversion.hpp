#pragma once

#include "mamba/concepts/bool_convertible.hpp"
#include "mamba/concepts/str_convertible.hpp"
#include "mamba/memory/read_only.hpp"
#include "mamba/types/bool.hpp"
#include "mamba/types/str.hpp"

namespace mamba::builtins {

template <concepts::BoolConvertibleObject T>
types::Bool AsBool(memory::ReadOnly<T> t) {
  return t->AsBool();
}

template <concepts::StrConvertibleObject T>
types::Str AsStr(memory::ReadOnly<T> t) {
  return t->AsStr();
}

template <concepts::Object T>
types::Str Repr(memory::ReadOnly<T> t) {
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
