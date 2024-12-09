#pragma once

#include "mamba/builtins/__types/big_int.hpp"
#include "mamba/builtins/__types/bool.hpp"
#include "mamba/builtins/__types/float.hpp"
#include "mamba/builtins/__types/int.hpp"
#include "mamba/builtins/__types/none.hpp"
#include "mamba/builtins/__types/object.hpp"

namespace mamba::builtins {

__types::Bool Bool(const __types::Object& t) {
  return t.__Bool__();
}

__types::Bool Bool(__types::BigInt i) {
  return i != 0;
}

__types::Bool Bool(__types::Bool b) {
  return b;
}

__types::Bool Bool(__types::Float f) {
  return f != 0.0;
}

__types::Bool Bool(__types::Int f) {
  return f != 0.0;
}

__types::Bool Bool(__types::None) {
  return false;
}

}  // namespace mamba::builtins
