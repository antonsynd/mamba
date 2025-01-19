#pragma once

#include "mamba/builtins/__types/bool.hpp"     // IWYU pragma: export
#include "mamba/builtins/__types/byte.hpp"     // IWYU pragma: export
#include "mamba/builtins/__types/complex.hpp"  // IWYU pragma: export
#include "mamba/builtins/__types/decimal.hpp"  // IWYU pragma: export
#include "mamba/builtins/__types/double.hpp"   // IWYU pragma: export
#include "mamba/builtins/__types/float.hpp"    // IWYU pragma: export
#include "mamba/builtins/__types/int.hpp"      // IWYU pragma: export
#include "mamba/builtins/__types/long.hpp"     // IWYU pragma: export
#include "mamba/builtins/__types/none.hpp"     // IWYU pragma: export
#include "mamba/builtins/__types/object.hpp"   // IWYU pragma: export
#include "mamba/builtins/__types/sbyte.hpp"    // IWYU pragma: export
#include "mamba/builtins/__types/short.hpp"    // IWYU pragma: export
#include "mamba/builtins/__types/size.hpp"     // IWYU pragma: export
#include "mamba/builtins/__types/ssize.hpp"    // IWYU pragma: export
#include "mamba/builtins/__types/str.hpp"      // IWYU pragma: export
#include "mamba/builtins/__types/uint.hpp"     // IWYU pragma: export
#include "mamba/builtins/__types/ulong.hpp"    // IWYU pragma: export
#include "mamba/builtins/__types/ushort.hpp"   // IWYU pragma: export

namespace mamba::builtins {

using BoolType = details::Bool;
using ByteType = details::Byte;
using ComplexType = details::Complex;
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
using SSizeType = details::SSize;
using StrType = details::Str;
using UIntType = details::UInt;
using ULongType = details::ULong;
using UShortType = details::UShort;

}  // namespace mamba::builtins
