#pragma once

#include "mamba/builtins/__types/bool.hpp"
#include "mamba/builtins/__types/int.hpp"

namespace mamba::builtins::__types {

struct Complex {
 public:
  Int Real() const { return real_; }
  Int Imag() const { return imag_; }

  Bool __Eq__(const Complex& other) const {
    return real_ == other.real_ && imag_ == other.imag_;
  }

  Bool __Ne__(const Complex& other) const { return !__Eq__(other); }

  bool operator==(const Complex& other) const { return __Eq__(other); }
  bool operator!=(const Complex& other) const { return !(*this == other); }

 private:
  Int real_;
  Int imag_;
};

}  // namespace mamba::builtins::__types

// IWYU pragma: private
