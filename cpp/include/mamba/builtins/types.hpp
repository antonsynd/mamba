#pragma once

#include "mamba/builtins/__types/big_int.hpp"  // IWYU pragma: export
#include "mamba/builtins/__types/bool.hpp"     // IWYU pragma: export
#include "mamba/builtins/__types/complex.hpp"  // IWYU pragma: export
#include "mamba/builtins/__types/double.hpp"   // IWYU pragma: export
#include "mamba/builtins/__types/float.hpp"    // IWYU pragma: export
#include "mamba/builtins/__types/int.hpp"      // IWYU pragma: export
#include "mamba/builtins/__types/none.hpp"     // IWYU pragma: export
#include "mamba/builtins/__types/object.hpp"   // IWYU pragma: export
#include "mamba/builtins/__types/str.hpp"      // IWYU pragma: export

namespace mamba::builtins {

using BigIntType = details::BigInt;
using BoolType = details::Bool;
using ComplexType = details::Complex;
using DoubleType = details::Double;
using FloatType = details::Float;
using IntType = details::Int;
using NoneType = details::None;
using ObjectType = details::Object;
using StrType = details::Str;

}  // namespace mamba::builtins
