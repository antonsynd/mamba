#pragma once

#include "mamba/builtins/__types/bool.hpp"
#include "mamba/builtins/__types/int.hpp"

namespace mamba::builtins::details {

struct Complex final {
 public:
  Int Real() const { return real_; }
  Int Imag() const { return imag_; }

  bool operator==(const Complex& other) const {
    return real_ == other.real_ && imag_ == other.imag_;
  }

  bool operator!=(const Complex& other) const { return !(*this == other); }

 private:
  Int real_;
  Int imag_;
};

}  // namespace mamba::builtins::details

// IWYU pragma: private
