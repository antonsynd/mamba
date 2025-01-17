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
  /// @note Mamba-specific alias for brevity.
  using self = Complex;

  /// @brief Returns the real part of this complex number.
  Double Real() const;

  /// @brief Returns the imaginary part of this complex number.
  Double Imag() const;

  /// @brief Returns true if any part of this number is non-zero. Returns false
  /// if both components are zero. Effectively, as long as the magnitude is
  /// non-zero, then this returns true.
  operator Bool() const;

  /// @brief Returns the representation of this number.
  Str __Repr__() const;

  /// @brief Returns the string conversion of this number. It is the same as
  /// __Repr__().
  operator Str() const;

  /// @brief Returns the magnitude of this number.
  Double __Abs__() const;

  // TODO: Implement arithmetic operators
  // self __Add__(const self& other) const;
  // self __Sub__(const self& other) const;
  // self __Mul__(const self& other) const;
  // self __TrueDiv__(const self& other) const;
  // self __Pow__(const self& other) const;

  // self __Add__(const Int i) const;
  // self __Sub__(const Int i) const;
  // self __Mul__(const Int i) const;
  // self __TrueDiv__(const Int i) const;
  // self __Pow__(const Int i) const;

  // self __Add__(const BigInt i) const;
  // self __Sub__(const BigInt i) const;
  // self __Mul__(const BigInt i) const;
  // self __TrueDiv__(const BigInt i) const;
  // self __Pow__(const BigInt i) const;

  // self __Add__(const Float f) const;
  // self __Sub__(const Float f) const;
  // self __Mul__(const Float f) const;
  // self __TrueDiv__(const Float f) const;
  // self __Pow__(const Float f) const;

  // self __Add__(const Double d) const;
  // self __Sub__(const Double d) const;
  // self __Mul__(const Double d) const;
  // self __TrueDiv__(const Double d) const;
  // self __Pow__(const Double d) const;

  // self __RAdd__(const self& other) const;
  // self __RSub__(const self& other) const;
  // self __RMul__(const self& other) const;
  // self __RTrueDiv__(const self& other) const;
  // self __RPow__(const self& other) const;

  // self __RAdd__(const Int i) const;
  // self __RSub__(const Int i) const;
  // self __RMul__(const Int i) const;
  // self __RTrueDiv__(const Int i) const;
  // self __RPow__(const Int i) const;

  // self __RAdd__(const BigInt i) const;
  // self __RSub__(const BigInt i) const;
  // self __RMul__(const BigInt i) const;
  // self __RTrueDiv__(const BigInt i) const;
  // self __RPow__(const BigInt i) const;

  // self __RAdd__(const Float f) const;
  // self __RSub__(const Float f) const;
  // self __RMul__(const Float f) const;
  // self __RTrueDiv__(const Float f) const;
  // self __RPow__(const Float f) const;

  // self __RAdd__(const Double d) const;
  // self __RSub__(const Double d) const;
  // self __RMul__(const Double d) const;
  // self __RTrueDiv__(const Double d) const;
  // self __RPow__(const Double d) const;

  // self& __IAdd__(const self& other) const;
  // self& __ISub__(const self& other) const;
  // self& __IMul__(const self& other) const;
  // self& __ITrueDiv__(const self& other) const;
  // self& __IPow__(const self& other) const;

  // self& __IAdd__(const Int i) const;
  // self& __ISub__(const Int i) const;
  // self& __IMul__(const Int i) const;
  // self& __ITrueDiv__(const Int i) const;
  // self& __IPow__(const Int i) const;

  // self& __IAdd__(const BigInt i) const;
  // self& __ISub__(const BigInt i) const;
  // self& __IMul__(const BigInt i) const;
  // self& __ITrueDiv__(const BigInt i) const;
  // self& __IPow__(const BigInt i) const;

  // self& __IAdd__(const Float f) const;
  // self& __ISub__(const Float f) const;
  // self& __IMul__(const Float f) const;
  // self& __ITrueDiv__(const Float f) const;
  // self& __IPow__(const Float f) const;

  // self& __IAdd__(const Double d) const;
  // self& __ISub__(const Double d) const;
  // self& __IMul__(const Double d) const;
  // self& __ITrueDiv__(const Double d) const;
  // self& __IPow__(const Double d) const;

  // self operator+(const self& other) const;
  // self operator-(const self& other) const;
  // self operator*(const self& other) const;
  // self operator/(const self& other) const;

  // self operator^(const Int i) const;
  // self operator^(const BigInt i) const;
  // self operator^(const Float f) const;
  // self operator^(const Double d) const;

  // self& operator+=(const self& other);
  // self& operator-=(const self& other);
  // self& operator*=(const self& other);
  // self& operator/=(const self& other);

  // self& operator^=(const Int i);
  // self& operator^=(const BigInt i);
  // self& operator^=(const Float f);
  // self& operator^=(const Double d);

  bool operator==(const self& other) const;
  bool operator!=(const self& other) const;

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
