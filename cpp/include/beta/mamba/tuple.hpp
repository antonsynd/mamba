#pragma once

#include <tuple>

namespace mamba::builtins {

template <typename... Args>
using tuple_t = std::tuple<... Args>;

}  // namespace mamba::builtins
