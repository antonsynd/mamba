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
  { t.AsBool() } -> std::same_as<types::Bool>;
};

template <typename T>
concept StrConvertible = requires(const T t) {
  { t.AsStr() } -> std::same_as<types::Str>;
};

}  // namespace mamba::builtins::concepts
