#include "mamba/builtins/repr.hpp"

#include <string>

#include "mamba/builtins/types.hpp"

namespace mamba::builtins {

StrType Repr(const BigIntType i) {
  return std::to_string(i);
}

StrType Repr(const BoolType b) {
  return b ? "True" : "False";
}

StrType Repr(const ComplexType& c) {
  return c.__Repr__();
}

StrType Repr(const DoubleType d) {
  return std::to_string(d);
}

StrType Repr(const FloatType f) {
  return std::to_string(f);
}

StrType Repr(const IntType i) {
  return std::to_string(i);
}

StrType Repr(const NoneType) {
  return "None";
}

StrType Repr(const ObjectType& t) {
  return t.__Repr__();
}

}  // namespace mamba::builtins
