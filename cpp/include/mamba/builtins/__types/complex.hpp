#pragma once

#include <cmath>
#include <string_view>

#include "mamba/builtins/__types/bool.hpp"
#include "mamba/builtins/__types/double.hpp"
#include "mamba/builtins/__types/str.hpp"
#include "mamba/builtins/__types/traits.hpp"

namespace mamba::builtins::details {

struct Complex final {
 public:
  Double Real() const { return real_; }
  Double Imag() const { return imag_; }

  // This is basically an object, but not.
  Bool __Eq__(const Complex& other) const {
    return real_ == other.real_ && imag_ == other.imag_;
  }

  bool operator==(const Complex& other) const { return __Eq__(other); }
  bool operator!=(const Complex& other) const { return !(*this == other); }

  // TODO: Implement arithmetic operators

  Bool __Bool__() const { return real_ != 0 && imag_ != 0; }
  explicit operator bool() const { return __Bool__(); }

  Str __Str__() const { return __Repr__(); }

  Str __Repr__() const {
    std::ostringstream oss;

    oss << "(" << std::to_string(real_);

    if (imag_ > 0.0) {
      oss << "+";
    }

    oss << std::to_string(imag_) << ")";

    return oss.str();
  }

  Double __Abs__() const { return std::hypot(real_, imag_); }

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
