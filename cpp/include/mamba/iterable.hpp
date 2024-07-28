#pragma once

#include <concepts>

#include "mamba/iterator.hpp"

namespace mamba::builtins::concepts {

// TODO: Fix Tuple<...>
template <typename T>
concept Iterable = requires(T t) {
  { t.Iter() } -> std::same_as<Iterator<T>>;
};

}  // namespace mamba::builtins::concepts
