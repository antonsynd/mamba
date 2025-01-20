#pragma once

#include <string>
#include <string_view>

#include "mamba/builtins/__types/traits.hpp"

namespace mamba::builtins::details {

// Forward-declaration
class ByteArray;

/// @brief Convenience overload for outputting to `std::cout`/`std::cerr` or
/// `std::ostringstream`.
std::ostream& operator<<(std::ostream& oss, const ByteArray& s);

/// @brief Constructs a `bytearray` via a literal.
ByteArray operator""_bytearray(const char* s, std::size_t len);

class ByteArray final {};

template <>
struct Traits<ByteArray> {
  static constexpr std::string_view kName = "bytearray";
};

}  // namespace mamba::builtins::details

// IWYU pragma: private
