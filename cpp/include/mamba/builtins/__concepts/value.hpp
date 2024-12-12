#pragma once

#include <concepts>

#include "mamba/builtins/__types/big_int.hpp"
#include "mamba/builtins/__types/bool.hpp"
#include "mamba/builtins/__types/complex.hpp"
#include "mamba/builtins/__types/float.hpp"
#include "mamba/builtins/__types/int.hpp"

namespace mamba::builtins::details {

template <typename T>
concept Value = std::same_as<std::decay_t<T>, Int> ||
                std::same_as<std::decay_t<T>, BigInt> ||
                std::same_as<std::decay_t<T>, Float> ||
                std::same_as<std::decay_t<T>, Bool> ||
                std::same_as<std::decay_t<T>, Complex>;

template <typename T>
concept NotValue = !Value<T>;

}  // namespace mamba::builtins::details

// IWYU pragma: private
