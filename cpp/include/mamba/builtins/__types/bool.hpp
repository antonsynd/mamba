#pragma once

#include <string_view>  // for basic_string_view, str...
#include "mamba/builtins/__meta/optional.hpp"
#include "mamba/builtins/__types/byte.hpp"     // for Byte
#include "mamba/builtins/__types/decimal.hpp"  // for Decimal
#include "mamba/builtins/__types/double.hpp"   // for Double
#include "mamba/builtins/__types/float.hpp"    // for Float
#include "mamba/builtins/__types/int.hpp"      // for Int
#include "mamba/builtins/__types/long.hpp"     // for Long
#include "mamba/builtins/__types/none.hpp"     // for None
#include "mamba/builtins/__types/sbyte.hpp"    // for SByte
#include "mamba/builtins/__types/short.hpp"    // for Short
#include "mamba/builtins/__types/size.hpp"     // for Size
#include "mamba/builtins/__types/traits.hpp"
#include "mamba/builtins/__types/uint.hpp"    // for UInt
#include "mamba/builtins/__types/ulong.hpp"   // for ULong
#include "mamba/builtins/__types/ushort.hpp"  // for UShort

namespace mamba::builtins::details {

/// @brief A proxy for the Pythonic `bool` type. In general, all Mamba APIs
/// that interact with bools should return the C++ `bool` type. This proxy
/// is meant to provide both an implicit conversion target via `operator Bool()`
/// on implementing classes, and the builtin conversion function `Bool()`.
/// The implicit conversion target is to avoid having implicit conversion
/// `operator bool()` be performed when trying to equate differing types, which
/// would yield incorrect results if there is an overload for `operator==()`.
///
/// @note This goes against the Python specification which says bool is an
/// integer. This is to ensure we can write overload built-in functions for
/// both Int and Bool.
struct Bool final {
 public:
  Bool();

  Bool(const bool b);
  Bool(const Byte b);
  Bool(const Decimal d);
  Bool(const Double d);
  Bool(const Float f);
  Bool(const Int i);
  Bool(const Long l);
  Bool(const None);
  Bool(const SByte s);
  Bool(const Short s);
  Bool(const Size s);
  Bool(const SSize s);
  Bool(const UInt u);
  Bool(const ULong u);
  Bool(const UShort u);

  template <IsOptional T>
  Bool(const T& o) {
    b_ = Unwrap(o).has_value();
  }

  // Converting constructor from Str is not defined here because it would
  // cause a circular reference, since Str itself has implicit conversion to
  // Bool in str.hpp.

  bool operator==(const Bool& other) const;
  bool operator!=(const Bool& other) const;

  // Note: Conversion to Str is defined in str.hpp via implicit conversion to
  // C++ bool to avoid circular references since Str itself has implicit
  // conversion to Bool.
  operator bool() const;
  operator Byte() const;
  operator Decimal() const;
  operator Double() const;
  operator Float() const;
  operator Int() const;
  operator Long() const;
  operator SByte() const;
  operator Short() const;
  operator Size() const;
  operator SSize() const;
  operator UInt() const;
  operator ULong() const;
  operator UShort() const;

 private:
  bool b_;
};

template <>
struct Traits<Bool> {
  static constexpr std::string_view kName = "bool";
};

}  // namespace mamba::builtins::details

// IWYU pragma: private
