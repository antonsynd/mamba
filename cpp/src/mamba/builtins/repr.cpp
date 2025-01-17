#include "mamba/builtins/repr.hpp"

#include "mamba/builtins/__types/object.hpp"  // for Object
#include "mamba/builtins/__types/str.hpp"     // for Str
#include "mamba/builtins/types.hpp"           // for StrType, ObjectType

namespace mamba::builtins {

StrType Repr(const BoolType b) {
  return b;
}

StrType Repr(const ByteType b) {
  return b;
}

// StrType Repr(const ComplexType& c) {
//   return c.__Repr__();
// }

StrType Repr(const DecimalType d) {
  return d;
}

StrType Repr(const DoubleType d) {
  return d;
}

StrType Repr(const FloatType f) {
  return f;
}

StrType Repr(const IntType i) {
  return i;
}

StrType Repr(const LongType l) {
  return l;
}

StrType Repr(const NoneType n) {
  return n;
}

StrType Repr(const ObjectType& o) {
  return o.__Repr__();
}

StrType Repr(const std::shared_ptr<ObjectType>& o) {
  return o->__Repr__();
}

StrType Repr(const SByteType s) {
  return s;
}

StrType Repr(const ShortType s) {
  return s;
}

StrType Repr(const SizeType s) {
  return s;
}

StrType Repr(const UIntType u) {
  return u;
}

StrType Repr(const ULongType u) {
  return u;
}

StrType Repr(const UShortType u) {
  return u;
}

}  // namespace mamba::builtins
