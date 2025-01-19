#pragma once

#include <string_view>  // for basic_string_view, stri...

#include "mamba/builtins/__types/bool.hpp"    // for Bool
#include "mamba/builtins/__types/double.hpp"  // for Double
#include "mamba/builtins/__types/str.hpp"     // for Str
#include "mamba/builtins/__types/traits.hpp"

namespace mamba::builtins::details {

/// @brief A complex number.
/// @note Internally, it has an API that is similar to Object, but it is not
/// one.
struct Complex final {
 public:
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

  // TODO: Implement arithmetic operators
  // Complex __Add__(const Complex& other) const;
  // Complex __Sub__(const Complex& other) const;
  // Complex __Mul__(const Complex& other) const;
  // Complex __TrueDiv__(const Complex& other) const;
  // Complex __Pow__(const Complex& other) const;

  // Complex __Add__(const Int i) const;
  // Complex __Sub__(const Int i) const;
  // Complex __Mul__(const Int i) const;
  // Complex __TrueDiv__(const Int i) const;
  // Complex __Pow__(const Int i) const;

  // Complex __Add__(const BigInt i) const;
  // Complex __Sub__(const BigInt i) const;
  // Complex __Mul__(const BigInt i) const;
  // Complex __TrueDiv__(const BigInt i) const;
  // Complex __Pow__(const BigInt i) const;

  // Complex __Add__(const Float f) const;
  // Complex __Sub__(const Float f) const;
  // Complex __Mul__(const Float f) const;
  // Complex __TrueDiv__(const Float f) const;
  // Complex __Pow__(const Float f) const;

  // Complex __Add__(const Double d) const;
  // Complex __Sub__(const Double d) const;
  // Complex __Mul__(const Double d) const;
  // Complex __TrueDiv__(const Double d) const;
  // Complex __Pow__(const Double d) const;

  // Complex __RAdd__(const Complex& other) const;
  // Complex __RSub__(const Complex& other) const;
  // Complex __RMul__(const Complex& other) const;
  // Complex __RTrueDiv__(const Complex& other) const;
  // Complex __RPow__(const Complex& other) const;

  // Complex __RAdd__(const Int i) const;
  // Complex __RSub__(const Int i) const;
  // Complex __RMul__(const Int i) const;
  // Complex __RTrueDiv__(const Int i) const;
  // Complex __RPow__(const Int i) const;

  // Complex __RAdd__(const BigInt i) const;
  // Complex __RSub__(const BigInt i) const;
  // Complex __RMul__(const BigInt i) const;
  // Complex __RTrueDiv__(const BigInt i) const;
  // Complex __RPow__(const BigInt i) const;

  // Complex __RAdd__(const Float f) const;
  // Complex __RSub__(const Float f) const;
  // Complex __RMul__(const Float f) const;
  // Complex __RTrueDiv__(const Float f) const;
  // Complex __RPow__(const Float f) const;

  // Complex __RAdd__(const Double d) const;
  // Complex __RSub__(const Double d) const;
  // Complex __RMul__(const Double d) const;
  // Complex __RTrueDiv__(const Double d) const;
  // Complex __RPow__(const Double d) const;

  // Complex& __IAdd__(const Complex& other) const;
  // Complex& __ISub__(const Complex& other) const;
  // Complex& __IMul__(const Complex& other) const;
  // Complex& __ITrueDiv__(const Complex& other) const;
  // Complex& __IPow__(const Complex& other) const;

  // Complex& __IAdd__(const Int i) const;
  // Complex& __ISub__(const Int i) const;
  // Complex& __IMul__(const Int i) const;
  // Complex& __ITrueDiv__(const Int i) const;
  // Complex& __IPow__(const Int i) const;

  // Complex& __IAdd__(const BigInt i) const;
  // Complex& __ISub__(const BigInt i) const;
  // Complex& __IMul__(const BigInt i) const;
  // Complex& __ITrueDiv__(const BigInt i) const;
  // Complex& __IPow__(const BigInt i) const;

  // Complex& __IAdd__(const Float f) const;
  // Complex& __ISub__(const Float f) const;
  // Complex& __IMul__(const Float f) const;
  // Complex& __ITrueDiv__(const Float f) const;
  // Complex& __IPow__(const Float f) const;

  // Complex& __IAdd__(const Double d) const;
  // Complex& __ISub__(const Double d) const;
  // Complex& __IMul__(const Double d) const;
  // Complex& __ITrueDiv__(const Double d) const;
  // Complex& __IPow__(const Double d) const;

  // Complex operator+(const Complex& other) const;
  // Complex operator-(const Complex& other) const;
  // Complex operator*(const Complex& other) const;
  // Complex operator/(const Complex& other) const;

  // Complex operator^(const Int i) const;
  // Complex operator^(const BigInt i) const;
  // Complex operator^(const Float f) const;
  // Complex operator^(const Double d) const;

  // Complex& operator+=(const Complex& other);
  // Complex& operator-=(const Complex& other);
  // Complex& operator*=(const Complex& other);
  // Complex& operator/=(const Complex& other);

  // Complex& operator^=(const Int i);
  // Complex& operator^=(const BigInt i);
  // Complex& operator^=(const Float f);
  // Complex& operator^=(const Double d);

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

}  // namespace mamba::builtins::details

// IWYU pragma: private
