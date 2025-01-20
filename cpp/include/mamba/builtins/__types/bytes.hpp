#pragma once

#include <string>
#include <string_view>

#include "mamba/builtins/__types/traits.hpp"

namespace mamba::builtins::details {

// Forward-declaration
class Bytes;

/// @brief Convenience overload for outputting to `std::cout`/`std::cerr` or
/// `std::ostringstream`.
std::ostream& operator<<(std::ostream& oss, const Bytes& s);

/// @brief Constructs a sequence of bytes via a literal.
Bytes operator""_bytes(const char* s, std::size_t len);

class Bytes final {};

template <>
struct Traits<Bytes> {
  static constexpr std::string_view kName = "bytes";
};

}  // namespace mamba::builtins::details

// IWYU pragma: private
