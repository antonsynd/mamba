#pragma once

#include <iomanip>
#include <iostream>

#include "mamba/builtins/__types/size.hpp"

namespace mamba::__utils {
namespace details {

struct HexPrinter {
 public:
  explicit HexPrinter(builtins::details::Size s) : s_(s) {}

  builtins::details::Size Value() const { return s_; }

 private:
  builtins::details::Size s_;
};

inline std::ostream& operator<<(std::ostream& oss, const HexPrinter& hp) {
  oss << std::hex << std::setfill('0') << std::setw(16) << hp.Value()
      << std::dec;

  return oss;
}

}  // namespace details

inline details::HexPrinter print_hex(builtins::details::Size s) {
  return details::HexPrinter(s);
}

}  // namespace mamba::__utils
