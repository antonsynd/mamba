#pragma once

#include "mamba/builtins/types.hpp"  // for Str, BigInt, Bool, Double

namespace mamba::builtins {

StrType Repr(const BigIntType i);
StrType Repr(const BoolType b);
StrType Repr(const ComplexType& c);
StrType Repr(const DoubleType d);
StrType Repr(const FloatType f);
StrType Repr(const IntType i);
StrType Repr(const NoneType);
StrType Repr(const ObjectType& t);

}  // namespace mamba::builtins
