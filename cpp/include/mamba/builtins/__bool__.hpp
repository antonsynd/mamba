#pragma once

#include "mamba/builtins/__types/big_int.hpp"
#include "mamba/builtins/__types/bool.hpp"
#include "mamba/builtins/__types/complex.hpp"
#include "mamba/builtins/__types/double.hpp"
#include "mamba/builtins/__types/float.hpp"
#include "mamba/builtins/__types/int.hpp"
#include "mamba/builtins/__types/none.hpp"
#include "mamba/builtins/__types/object.hpp"

namespace mamba::builtins {

details::Bool Bool(const details::BigInt i) {
  return i != 0;
}

details::Bool Bool(const details::Bool b) {
  return b;
}

details::Bool Bool(const details::Complex& c) {
  return c.__Bool__();
}

details::Bool Bool(const details::Double d) {
  return d != 0.0;
}

details::Bool Bool(const details::Float f) {
  return f != 0.0;
}

details::Bool Bool(const details::Int i) {
  return i != 0.0;
}

details::Bool Bool(const details::None) {
  return false;
}

details::Bool Bool(const details::Object& t) {
  return t.__Bool__();
}

}  // namespace mamba::builtins
