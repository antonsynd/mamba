#pragma once

#include <string_view>  // for basic_string_view, stri...

#include "mamba/builtins/__types/bool.hpp"     // for Bool
#include "mamba/builtins/__types/byte.hpp"     // for Bool
#include "mamba/builtins/__types/decimal.hpp"  // for Bool
#include "mamba/builtins/__types/double.hpp"   // for Double
#include "mamba/builtins/__types/float.hpp"    // for Bool
#include "mamba/builtins/__types/int.hpp"      // for Bool
#include "mamba/builtins/__types/long.hpp"     // for Bool
#include "mamba/builtins/__types/sbyte.hpp"    // for Bool
#include "mamba/builtins/__types/short.hpp"    // for Bool
#include "mamba/builtins/__types/size.hpp"     // for Bool
#include "mamba/builtins/__types/ssize.hpp"    // for Bool
#include "mamba/builtins/__types/str.hpp"      // for Str
#include "mamba/builtins/__types/traits.hpp"
#include "mamba/builtins/__types/uint.hpp"    // for Bool
#include "mamba/builtins/__types/ulong.hpp"   // for Bool
#include "mamba/builtins/__types/ushort.hpp"  // for Bool

namespace mamba::builtins::details {

/// @brief A complex number.
/// @note Internally, it has an API that is similar to Object, but it is not
/// one.
struct Complex final {
 public:
  explicit Complex(Double real = 0, Double imag = 0)
      : real_(real), imag_(imag) {}

  /// @brief Returns the real part of this complex number.
  Double Real() const;

  /// @brief Returns the imaginary part of this complex number.
  Double Imag() const;

  /// @brief Returns true if any part of this number is non-zero. Returns false
  /// if both components are zero. Effectively, as long as the magnitude is
  /// non-zero, then this returns true.
  operator Bool() const;

  /// @brief Returns the representation of this number.
  Str Repr() const;

  /// @brief Returns the string conversion of this number. It is the same as
  /// Repr().
  operator Str() const;

  /// @brief Returns the magnitude of this number.
  Double Abs() const;

  Complex operator+(const Byte& b) const;
  Complex operator+(const Complex& c) const;
  Complex operator+(const Decimal d) const;
  Complex operator+(const Double d) const;
  Complex operator+(const Float f) const;
  Complex operator+(const Int i) const;
  Complex operator+(const Long l) const;
  Complex operator+(const SByte& s) const;
  Complex operator+(const Short s) const;
  Complex operator+(const Size s) const;
  Complex operator+(const SSize s) const;
  Complex operator+(const UInt u) const;
  Complex operator+(const ULong u) const;
  Complex operator+(const UShort u) const;

  Complex operator-(const Byte& b) const;
  Complex operator-(const Complex& c) const;
  Complex operator-(const Decimal d) const;
  Complex operator-(const Double d) const;
  Complex operator-(const Float f) const;
  Complex operator-(const Int i) const;
  Complex operator-(const Long l) const;
  Complex operator-(const SByte& s) const;
  Complex operator-(const Short s) const;
  Complex operator-(const Size s) const;
  Complex operator-(const SSize s) const;
  Complex operator-(const UInt u) const;
  Complex operator-(const ULong u) const;
  Complex operator-(const UShort u) const;

  Complex operator*(const Byte& b) const;
  Complex operator*(const Complex& c) const;
  Complex operator*(const Decimal d) const;
  Complex operator*(const Double d) const;
  Complex operator*(const Float f) const;
  Complex operator*(const Int i) const;
  Complex operator*(const Long l) const;
  Complex operator*(const SByte& s) const;
  Complex operator*(const Short s) const;
  Complex operator*(const Size s) const;
  Complex operator*(const SSize s) const;
  Complex operator*(const UInt u) const;
  Complex operator*(const ULong u) const;
  Complex operator*(const UShort u) const;

  Complex operator/(const Byte& b) const;
  Complex operator/(const Complex& c) const;
  Complex operator/(const Decimal d) const;
  Complex operator/(const Double d) const;
  Complex operator/(const Float f) const;
  Complex operator/(const Int i) const;
  Complex operator/(const Long l) const;
  Complex operator/(const SByte& s) const;
  Complex operator/(const Short s) const;
  Complex operator/(const Size s) const;
  Complex operator/(const SSize s) const;
  Complex operator/(const UInt u) const;
  Complex operator/(const ULong u) const;
  Complex operator/(const UShort u) const;

  Complex operator^(const Byte& b) const;
  Complex operator^(const Complex& c) const;
  Complex operator^(const Decimal d) const;
  Complex operator^(const Double d) const;
  Complex operator^(const Float f) const;
  Complex operator^(const Int i) const;
  Complex operator^(const Long l) const;
  Complex operator^(const SByte& s) const;
  Complex operator^(const Short s) const;
  Complex operator^(const Size s) const;
  Complex operator^(const SSize s) const;
  Complex operator^(const UInt u) const;
  Complex operator^(const ULong u) const;
  Complex operator^(const UShort u) const;

  Complex& operator+=(const Byte& b);
  Complex& operator+=(const Complex& c);
  Complex& operator+=(const Decimal d);
  Complex& operator+=(const Double d);
  Complex& operator+=(const Float f);
  Complex& operator+=(const Int i);
  Complex& operator+=(const Long l);
  Complex& operator+=(const SByte& s);
  Complex& operator+=(const Short s);
  Complex& operator+=(const Size s);
  Complex& operator+=(const SSize s);
  Complex& operator+=(const UInt u);
  Complex& operator+=(const ULong u);
  Complex& operator+=(const UShort u);

  Complex& operator-=(const Byte& b);
  Complex& operator-=(const Complex& c);
  Complex& operator-=(const Decimal d);
  Complex& operator-=(const Double d);
  Complex& operator-=(const Float f);
  Complex& operator-=(const Int i);
  Complex& operator-=(const Long l);
  Complex& operator-=(const SByte& s);
  Complex& operator-=(const Short s);
  Complex& operator-=(const Size s);
  Complex& operator-=(const SSize s);
  Complex& operator-=(const UInt u);
  Complex& operator-=(const ULong u);
  Complex& operator-=(const UShort u);

  Complex& operator*=(const Byte& b);
  Complex& operator*=(const Complex& c);
  Complex& operator*=(const Decimal d);
  Complex& operator*=(const Double d);
  Complex& operator*=(const Float f);
  Complex& operator*=(const Int i);
  Complex& operator*=(const Long l);
  Complex& operator*=(const SByte& s);
  Complex& operator*=(const Short s);
  Complex& operator*=(const Size s);
  Complex& operator*=(const SSize s);
  Complex& operator*=(const UInt u);
  Complex& operator*=(const ULong u);
  Complex& operator*=(const UShort u);

  Complex& operator/=(const Byte& b);
  Complex& operator/=(const Complex& c);
  Complex& operator/=(const Decimal d);
  Complex& operator/=(const Double d);
  Complex& operator/=(const Float f);
  Complex& operator/=(const Int i);
  Complex& operator/=(const Long l);
  Complex& operator/=(const SByte& s);
  Complex& operator/=(const Short s);
  Complex& operator/=(const Size s);
  Complex& operator/=(const SSize s);
  Complex& operator/=(const UInt u);
  Complex& operator/=(const ULong u);
  Complex& operator/=(const UShort u);

  Complex& operator^=(const Byte& b);
  Complex& operator^=(const Complex& c);
  Complex& operator^=(const Decimal d);
  Complex& operator^=(const Double d);
  Complex& operator^=(const Float f);
  Complex& operator^=(const Int i);
  Complex& operator^=(const Long l);
  Complex& operator^=(const SByte& s);
  Complex& operator^=(const Short s);
  Complex& operator^=(const Size s);
  Complex& operator^=(const SSize s);
  Complex& operator^=(const UInt u);
  Complex& operator^=(const ULong u);
  Complex& operator^=(const UShort u);

  bool operator==(const Complex& other) const;
  bool operator!=(const Complex& other) const;

 private:
  Double real_;
  Double imag_;
};

template <>
struct Traits<Complex> {
  static constexpr std::string_view kName = "complex";
};

Complex operator""_j(const char* s, const std::size_t len) {
  return Complex(0, 0);
}

}  // namespace mamba::builtins::details

// IWYU pragma: private
