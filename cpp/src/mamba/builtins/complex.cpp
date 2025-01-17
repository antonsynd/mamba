#include "mamba/builtins/__types/complex.hpp"

#include <cmath>    // for hypot
#include <sstream>  // for char_traits, basic_ostr...
#include <string>   // for allocator, to_string

#include "mamba/builtins/__types/bool.hpp"    // for Bool
#include "mamba/builtins/__types/double.hpp"  // for Double
#include "mamba/builtins/__types/str.hpp"     // for Str

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

Str Complex::__Repr__() const {
  std::ostringstream oss;

  oss << "(" << std::to_string(real_);

  if (imag_ > 0.0) {
    oss << "+";
  }

  oss << std::to_string(imag_) << ")";

  return oss.str();
}

Complex::operator Str() const {
  return __Repr__();
}

Double Complex::__Abs__() const {
  return std::hypot(real_, imag_);
}

bool Complex::operator==(const Complex& other) const {
  return real_ == other.real_ && imag_ == other.imag_;
}

bool Complex::operator!=(const Complex& other) const {
  return !(*this == other);
}

}  // namespace mamba::builtins::details
