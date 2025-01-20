#include "mamba/builtins/__types/complex.hpp"

#include <cmath>    // for hypot
#include <sstream>  // for char_traits, basic_ostr...
#include <string>   // for allocator, to_string

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
#include "mamba/builtins/__types/uint.hpp"     // for Bool
#include "mamba/builtins/__types/ulong.hpp"    // for Bool
#include "mamba/builtins/__types/ushort.hpp"   // for Bool

namespace mamba::builtins::details {

Double Complex::Real() const {
  return real_;
}
Double Complex::Imag() const {
  return imag_;
}

Complex::operator Bool() const {
  return real_ != 0 && imag_ != 0;
}

Str Complex::Repr() const {
  std::ostringstream oss;

  oss << "(" << std::to_string(real_);

  if (imag_ > 0.0) {
    oss << "+";
  }

  oss << std::to_string(imag_) << ")";

  return oss.str();
}

Complex::operator Str() const {
  return Repr();
}

Double Complex::Abs() const {
  return std::hypot(real_, imag_);
}

Complex Complex::operator+(const Byte b) const {
  return *this;
}

Complex Complex::operator+(const Complex& c) const {
  return *this;
}

Complex Complex::operator+(const Decimal d) const {
  return *this;
}

Complex Complex::operator+(const Double d) const {
  return *this;
}

Complex Complex::operator+(const Float f) const {
  return *this;
}

Complex Complex::operator+(const Int i) const {
  return *this;
}

Complex Complex::operator+(const Long l) const {
  return *this;
}

Complex Complex::operator+(const SByte s) const {
  return *this;
}

Complex Complex::operator+(const Short s) const {
  return *this;
}

Complex Complex::operator+(const Size s) const {
  return *this;
}

Complex Complex::operator+(const SSize s) const {
  return *this;
}

Complex Complex::operator+(const UInt u) const {
  return *this;
}

Complex Complex::operator+(const ULong u) const {
  return *this;
}

Complex Complex::operator+(const UShort u) const {
  return *this;
}

Complex Complex::operator-(const Byte b) const {
  return *this;
}

Complex Complex::operator-(const Complex& c) const {
  return *this;
}

Complex Complex::operator-(const Decimal d) const {
  return *this;
}

Complex Complex::operator-(const Double d) const {
  return *this;
}

Complex Complex::operator-(const Float f) const {
  return *this;
}

Complex Complex::operator-(const Int i) const {
  return *this;
}

Complex Complex::operator-(const Long l) const {
  return *this;
}

Complex Complex::operator-(const SByte s) const {
  return *this;
}

Complex Complex::operator-(const Short s) const {
  return *this;
}

Complex Complex::operator-(const Size s) const {
  return *this;
}

Complex Complex::operator-(const SSize s) const {
  return *this;
}

Complex Complex::operator-(const UInt u) const {
  return *this;
}

Complex Complex::operator-(const ULong u) const {
  return *this;
}

Complex Complex::operator-(const UShort u) const {
  return *this;
}

Complex Complex::operator*(const Byte b) const {
  return *this;
}

Complex Complex::operator*(const Complex& c) const {
  return *this;
}

Complex Complex::operator*(const Decimal d) const {
  return *this;
}

Complex Complex::operator*(const Double d) const {
  return *this;
}

Complex Complex::operator*(const Float f) const {
  return *this;
}

Complex Complex::operator*(const Int i) const {
  return *this;
}

Complex Complex::operator*(const Long l) const {
  return *this;
}

Complex Complex::operator*(const SByte s) const {
  return *this;
}

Complex Complex::operator*(const Short s) const {
  return *this;
}

Complex Complex::operator*(const Size s) const {
  return *this;
}

Complex Complex::operator*(const SSize s) const {
  return *this;
}

Complex Complex::operator*(const UInt u) const {
  return *this;
}

Complex Complex::operator*(const ULong u) const {
  return *this;
}

Complex Complex::operator*(const UShort u) const {
  return *this;
}

Complex Complex::operator/(const Byte b) const {
  return *this;
}

Complex Complex::operator/(const Complex& c) const {
  return *this;
}

Complex Complex::operator/(const Decimal d) const {
  return *this;
}

Complex Complex::operator/(const Double d) const {
  return *this;
}

Complex Complex::operator/(const Float f) const {
  return *this;
}

Complex Complex::operator/(const Int i) const {
  return *this;
}

Complex Complex::operator/(const Long l) const {
  return *this;
}

Complex Complex::operator/(const SByte s) const {
  return *this;
}

Complex Complex::operator/(const Short s) const {
  return *this;
}

Complex Complex::operator/(const Size s) const {
  return *this;
}

Complex Complex::operator/(const SSize s) const {
  return *this;
}

Complex Complex::operator/(const UInt u) const {
  return *this;
}

Complex Complex::operator/(const ULong u) const {
  return *this;
}

Complex Complex::operator/(const UShort u) const {
  return *this;
}

Complex Complex::operator^(const Byte b) const {
  return *this;
}

Complex Complex::operator^(const Complex& c) const {
  return *this;
}

Complex Complex::operator^(const Decimal d) const {
  return *this;
}

Complex Complex::operator^(const Double d) const {
  return *this;
}

Complex Complex::operator^(const Float f) const {
  return *this;
}

Complex Complex::operator^(const Int i) const {
  return *this;
}

Complex Complex::operator^(const Long l) const {
  return *this;
}

Complex Complex::operator^(const SByte s) const {
  return *this;
}

Complex Complex::operator^(const Short s) const {
  return *this;
}

Complex Complex::operator^(const Size s) const {
  return *this;
}

Complex Complex::operator^(const SSize s) const {
  return *this;
}

Complex Complex::operator^(const UInt u) const {
  return *this;
}

Complex Complex::operator^(const ULong u) const {
  return *this;
}

Complex Complex::operator^(const UShort u) const {
  return *this;
}

Complex& Complex::operator+=(const Byte b) {
  return *this;
}

Complex& Complex::operator+=(const Complex& c) {
  return *this;
}

Complex& Complex::operator+=(const Decimal d) {
  return *this;
}

Complex& Complex::operator+=(const Double d) {
  return *this;
}

Complex& Complex::operator+=(const Float f) {
  return *this;
}

Complex& Complex::operator+=(const Int i) {
  return *this;
}

Complex& Complex::operator+=(const Long l) {
  return *this;
}

Complex& Complex::operator+=(const SByte s) {
  return *this;
}

Complex& Complex::operator+=(const Short s) {
  return *this;
}

Complex& Complex::operator+=(const Size s) {
  return *this;
}

Complex& Complex::operator+=(const SSize s) {
  return *this;
}

Complex& Complex::operator+=(const UInt u) {
  return *this;
}

Complex& Complex::operator+=(const ULong u) {
  return *this;
}

Complex& Complex::operator+=(const UShort u) {
  return *this;
}

Complex& Complex::operator-=(const Byte b) {
  return *this;
}

Complex& Complex::operator-=(const Complex& c) {
  return *this;
}

Complex& Complex::operator-=(const Decimal d) {
  return *this;
}

Complex& Complex::operator-=(const Double d) {
  return *this;
}

Complex& Complex::operator-=(const Float f) {
  return *this;
}

Complex& Complex::operator-=(const Int i) {
  return *this;
}

Complex& Complex::operator-=(const Long l) {
  return *this;
}

Complex& Complex::operator-=(const SByte s) {
  return *this;
}

Complex& Complex::operator-=(const Short s) {
  return *this;
}

Complex& Complex::operator-=(const Size s) {
  return *this;
}

Complex& Complex::operator-=(const SSize s) {
  return *this;
}

Complex& Complex::operator-=(const UInt u) {
  return *this;
}

Complex& Complex::operator-=(const ULong u) {
  return *this;
}

Complex& Complex::operator-=(const UShort u) {
  return *this;
}

Complex& Complex::operator*=(const Byte b) {
  return *this;
}

Complex& Complex::operator*=(const Complex& c) {
  return *this;
}

Complex& Complex::operator*=(const Decimal d) {
  return *this;
}

Complex& Complex::operator*=(const Double d) {
  return *this;
}

Complex& Complex::operator*=(const Float f) {
  return *this;
}

Complex& Complex::operator*=(const Int i) {
  return *this;
}

Complex& Complex::operator*=(const Long l) {
  return *this;
}

Complex& Complex::operator*=(const SByte s) {
  return *this;
}

Complex& Complex::operator*=(const Short s) {
  return *this;
}

Complex& Complex::operator*=(const Size s) {
  return *this;
}

Complex& Complex::operator*=(const SSize s) {
  return *this;
}

Complex& Complex::operator*=(const UInt u) {
  return *this;
}

Complex& Complex::operator*=(const ULong u) {
  return *this;
}

Complex& Complex::operator*=(const UShort u) {
  return *this;
}

Complex& Complex::operator/=(const Byte b) {
  return *this;
}

Complex& Complex::operator/=(const Complex& c) {
  return *this;
}

Complex& Complex::operator/=(const Decimal d) {
  return *this;
}

Complex& Complex::operator/=(const Double d) {
  return *this;
}

Complex& Complex::operator/=(const Float f) {
  return *this;
}

Complex& Complex::operator/=(const Int i) {
  return *this;
}

Complex& Complex::operator/=(const Long l) {
  return *this;
}

Complex& Complex::operator/=(const SByte s) {
  return *this;
}

Complex& Complex::operator/=(const Short s) {
  return *this;
}

Complex& Complex::operator/=(const Size s) {
  return *this;
}

Complex& Complex::operator/=(const SSize s) {
  return *this;
}

Complex& Complex::operator/=(const UInt u) {
  return *this;
}

Complex& Complex::operator/=(const ULong u) {
  return *this;
}

Complex& Complex::operator/=(const UShort u) {
  return *this;
}

Complex& Complex::operator^=(const Byte b) {
  return *this;
}

Complex& Complex::operator^=(const Complex& c) {
  return *this;
}

Complex& Complex::operator^=(const Decimal d) {
  return *this;
}

Complex& Complex::operator^=(const Double d) {
  return *this;
}

Complex& Complex::operator^=(const Float f) {
  return *this;
}

Complex& Complex::operator^=(const Int i) {
  return *this;
}

Complex& Complex::operator^=(const Long l) {
  return *this;
}

Complex& Complex::operator^=(const SByte s) {
  return *this;
}

Complex& Complex::operator^=(const Short s) {
  return *this;
}

Complex& Complex::operator^=(const Size s) {
  return *this;
}

Complex& Complex::operator^=(const SSize s) {
  return *this;
}

Complex& Complex::operator^=(const UInt u) {
  return *this;
}

Complex& Complex::operator^=(const ULong u) {
  return *this;
}

Complex& Complex::operator^=(const UShort u) {
  return *this;
}

bool Complex::operator==(const Complex& other) const {
  return real_ == other.real_ && imag_ == other.imag_;
}

bool Complex::operator!=(const Complex& other) const {
  return !(*this == other);
}

Complex operator""_j(const char* s, const std::size_t len) {
  return Complex(0, 0);
}

}  // namespace mamba::builtins::details
