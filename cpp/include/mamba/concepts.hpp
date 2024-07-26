#pragma once

#include <concepts>

#include "mamba/bool.hpp"
#include "mamba/float.hpp"
#include "mamba/int.hpp"
#include "mamba/iterator.hpp"
#include "mamba/list.hpp"
#include "mamba/none.hpp"
#include "mamba/str.hpp"
#include "mamba/tuple.hpp"

namespace mamba::builtins::concepts {

template <typename T>
concept BoolConvertible = requires(const T t) {
  { t.AsBool() } -> std::same_as<Bool>;
};

template <typename T>
concept StrConvertible = requires(const T t) {
  { t.AsStr() } -> std::same_as<Str>;
};

// TODO: Fix Tuple<...>
template <typename T>
concept Value = std::same_as<T, Int> || std::same_as<T, Float> ||
                std::same_as<T, Bool> || std::same_as<T, None>;

// TODO: Fix Tuple<...>
template <typename T, typename E>
concept Iterable = requires(T t) {
  { t.Iter() } -> std::same_as<Iterator<E>>;
};

}  // namespace mamba::builtins::concepts
