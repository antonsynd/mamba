#pragma once

#include "mamba/builtins/__types/value.hpp"  // IWYU pragma: export

namespace mamba::builtins {

using BoolType = details::Bool;
using ByteType = details::Byte;
// using ComplexType = details::Complex;
using DecimalType = details::Decimal;
using DoubleType = details::Double;
using FloatType = details::Float;
using IntType = details::Int;
using LongType = details::Long;
using NoneType = details::None;
using ObjectType = details::Object;
using SByteType = details::SByte;
using ShortType = details::Short;
using SizeType = details::Size;
using StrType = details::Str;
using UIntType = details::UInt;
using ULongType = details::ULong;
using UShortType = details::UShort;

}  // namespace mamba::builtins
