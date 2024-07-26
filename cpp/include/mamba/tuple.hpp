#pragma once

#include <tuple>

namespace mamba::builtins {

template <typename... Args>
using Tuple = std::tuple<... Args>;

}  // namespace mamba::builtins
