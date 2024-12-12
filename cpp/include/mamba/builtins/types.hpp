#pragma once

#include "mamba/builtins/__types/big_int.hpp"  // IWYU pragma: export
#include "mamba/builtins/__types/bool.hpp"     // IWYU pragma: export
#include "mamba/builtins/__types/complex.hpp"  // IWYU pragma: export
#include "mamba/builtins/__types/float.hpp"    // IWYU pragma: export
#include "mamba/builtins/__types/none.hpp"     // IWYU pragma: export
#include "mamba/builtins/__types/object.hpp"   // IWYU pragma: export
#include "mamba/builtins/__types/str.hpp"      // IWYU pragma: export

namespace mamba::builtins {

using BigIntType = details::BigInt;
using FloatType = details::Float;
using ComplexType = details::Complex;
using ObjectType = details::Object;
using BoolType = details::Bool;
using StrType = details::Str;
using IntType = details::Int;
using NoneType = details::None;

}  // namespace mamba::builtins
