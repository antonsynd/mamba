#pragma once

#include <string>

#include "mamba/builtins/__types/big_int.hpp"
#include "mamba/builtins/__types/bool.hpp"
#include "mamba/builtins/__types/complex.hpp"
#include "mamba/builtins/__types/double.hpp"
#include "mamba/builtins/__types/float.hpp"
#include "mamba/builtins/__types/int.hpp"
#include "mamba/builtins/__types/none.hpp"
#include "mamba/builtins/__types/object.hpp"
#include "mamba/builtins/__types/str.hpp"

namespace mamba::builtins {

details::Str Repr(const details::BigInt i) {
  return std::to_string(i);
}

details::Str Repr(const details::Bool b) {
  return b ? "True" : "False";
}

details::Str Repr(const details::Complex& c) {
  return c.__Repr__();
}

details::Str Repr(const details::Double d) {
  return std::to_string(d);
}

details::Str Repr(const details::Float f) {
  return std::to_string(f);
}

details::Str Repr(const details::Int i) {
  return std::to_string(i);
}

details::Str Repr(const details::None) {
  return "None";
}

details::Str Repr(const details::Object& t) {
  return t.__Repr__();
}

}  // namespace mamba::builtins
