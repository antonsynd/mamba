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

details::Str Str(const details::BigInt i) {
  return std::to_string(i);
}

details::Str Str(const details::Bool b) {
  return b ? "True" : "False";
}

details::Str Str(const details::Complex& c) {
  return c.__Str__();
}

details::Str Str(const details::Double d) {
  return std::to_string(d);
}

details::Str Str(const details::Float f) {
  return std::to_string(f);
}

details::Str Str(const details::Int i) {
  return std::to_string(i);
}

details::Str Str(const details::None) {
  return "None";
}

details::Str Str(const details::Object& t) {
  return t.__Str__();
}

}  // namespace mamba::builtins
