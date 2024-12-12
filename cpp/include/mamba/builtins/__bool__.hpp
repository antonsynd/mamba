#pragma once

#include "mamba/builtins/__types/big_int.hpp"
#include "mamba/builtins/__types/bool.hpp"
#include "mamba/builtins/__types/complex.hpp"
#include "mamba/builtins/__types/float.hpp"
#include "mamba/builtins/__types/int.hpp"
#include "mamba/builtins/__types/none.hpp"
#include "mamba/builtins/__types/object.hpp"

namespace mamba::builtins {

details::Bool Bool(const details::Object& t) {
  return t.__Bool__();
}

details::Bool Bool(details::BigInt i) {
  return i != 0;
}

details::Bool Bool(details::Bool b) {
  return b;
}

details::Bool Bool(details::Float f) {
  return f != 0.0;
}

details::Bool Bool(details::Int f) {
  return f != 0.0;
}

details::Bool Bool(details::None) {
  return false;
}

}  // namespace mamba::builtins
