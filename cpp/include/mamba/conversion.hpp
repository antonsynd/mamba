#pragma once

#include <concepts>
#include <type_traits>
#include <utility>

#include "mamba/concepts/bool_convertible.hpp"
#include "mamba/concepts/object.hpp"
#include "mamba/concepts/str_convertible.hpp"
#include "mamba/memory/handle.hpp"
#include "mamba/types/bool.hpp"
#include "mamba/types/str.hpp"

namespace mamba::builtins {

template <concepts::BoolConvertible T>
types::Bool AsBool(const T& t) {
  return t.AsBool();
}

template <concepts::BoolConvertible T>
types::Bool AsBool(const memory::Handle<T>& t) {
  return t->AsBool();
}

template <concepts::StrConvertible T>
types::Str AsStr(const T& t) {
  return t.AsStr();
}

template <concepts::StrConvertible T>
types::Str AsStr(const memory::Handle<T>& t) {
  return t->AsStr();
}

template <concepts::Object T>
types::Str Repr(const T& t) {
  return t.Repr();
}

template <concepts::Object T>
types::Str Repr(const memory::Handle<T>& t) {
  return t->Repr();
}

}  // namespace mamba::builtins
