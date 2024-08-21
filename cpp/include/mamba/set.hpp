#pragma once

#include <unordered_set>

#include "mamba/concepts/entity.hpp"

namespace mamba::builtins {

template <concepts::Entity T>
using Set = std::unordered_set<T>;

}  // namespace mamba::builtins
