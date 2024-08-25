#pragma once

#include <unordered_set>

#include "mamba/__concepts/entity.hpp"

namespace mamba::builtins {

template <__concepts::Entity T>
using Set = std::unordered_set<T>;

}  // namespace mamba::builtins
