#pragma once

#include <iomanip>
#include <iostream>

#include "mamba/builtins/__types/big_int.hpp"

namespace mamba::__utils {
namespace details {

struct HexPrinter {
 public:
  explicit HexPrinter(builtins::details::BigInt i) : i_(i) {}

  builtins::details::BigInt Value() const { return i_; }

 private:
  builtins::details::BigInt i_;
};

inline std::ostream& operator<<(std::ostream& oss, const HexPrinter& hp) {
  oss << std::hex << std::setfill('0') << std::setw(16) << hp.Value()
      << std::dec;

  return oss;
}

}  // namespace details

inline details::HexPrinter print_hex(builtins::details::BigInt i) {
  return details::HexPrinter(i);
}

}  // namespace mamba::__utils
