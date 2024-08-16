#pragma once

#include <tuple>

namespace mamba::builtins::types {

template <typename... Args>
using Tuple = std::tuple<Args...>;

}  // namespace mamba::builtins::types
