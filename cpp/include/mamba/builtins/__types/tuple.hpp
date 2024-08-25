#pragma once

#include <tuple>

namespace mamba::builtins::__types {

template <typename... Args>
using Tuple = std::tuple<Args...>;

}  // namespace mamba::builtins::__types

// IWYU pragma: private
