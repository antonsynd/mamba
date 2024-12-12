#pragma once

#include <string>

#include "mamba/builtins/__types/big_int.hpp"
#include "mamba/builtins/__types/bool.hpp"
#include "mamba/builtins/__types/complex.hpp"
#include "mamba/builtins/__types/float.hpp"
#include "mamba/builtins/__types/int.hpp"
#include "mamba/builtins/__types/none.hpp"
#include "mamba/builtins/__types/object.hpp"
#include "mamba/builtins/__types/str.hpp"
#include "mamba/builtins/__types/tuple.hpp"

namespace mamba::builtins {

details::Str Str(const details::Object& t) {
  return t.__Str__();
}

details::Str Str(details::BigInt i) {
  return std::to_string(i);
}

details::Str Str(details::Bool b) {
  return b ? "True" : "False";
}

details::Str Str(details::Float f) {
  return std::to_string(f);
}

details::Str Str(details::Int i) {
  return std::to_string(i);
}

details::Str Str(details::None) {
  return "None";
}

}  // namespace mamba::builtins
