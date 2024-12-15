#pragma once

#include <string>
#include <string_view>

#include "mamba/builtins/__types/traits.hpp"

namespace mamba::builtins::details {

using Bytes = std::string;

template <>
struct Traits<Bytes> {
  static constexpr std::string_view kName = "bytes";
};

}  // namespace mamba::builtins::details

// IWYU pragma: private
