#pragma once

#include <concepts>

#include "mamba/builtins/__types/bool.hpp"
#include "mamba/builtins/__types/complex.hpp"
#include "mamba/builtins/__types/float.hpp"
#include "mamba/builtins/__types/int.hpp"

namespace mamba::builtins::__concepts {

template <typename T>
concept Value =
    std::same_as<T, __types::Int> || std::same_as<T, __types::Float> ||
    std::same_as<T, __types::Bool> || std::same_as<T, __types::Complex>;

}  // namespace mamba::builtins::__concepts

// IWYU pragma: private
