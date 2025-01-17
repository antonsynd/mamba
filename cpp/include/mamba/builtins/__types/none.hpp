#pragma once

#include <optional>

namespace mamba::builtins::details {

using None = std::nullopt_t;

constexpr auto kNone = std::nullopt;

}  // namespace mamba::builtins::details

// IWYU pragma: private
