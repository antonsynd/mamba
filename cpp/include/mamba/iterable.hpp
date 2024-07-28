#pragma once

#include <concepts>

#include "mamba/iterator.hpp"

namespace mamba::builtins::concepts {

// TODO: Fix Tuple<...>
template <typename T, typename E>
concept Iterable = requires(T t) {
  { t.Iter() } -> std::same_as<Iterator<E>>;
};

}  // namespace mamba::builtins::concepts
