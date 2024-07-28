#pragma once

#include <concepts>

#include "mamba/bool.hpp"
#include "mamba/float.hpp"
#include "mamba/int.hpp"
#include "mamba/none.hpp"
#include "mamba/str.hpp"
#include "mamba/tuple.hpp"

namespace mamba::builtins::concepts {

// TODO: Fix Tuple<...>
template <typename T>
concept Value = std::same_as<T, types::Int> || std::same_as<T, types::Float> ||
                std::same_as<T, types::Bool> || std::same_as<T, types::None>;

}  // namespace mamba::builtins::concepts
