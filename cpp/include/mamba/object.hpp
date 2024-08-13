#pragma once

#include <concepts>
#include <type_traits>

#include "mamba/concepts.hpp"
#include "mamba/str.hpp"
#include "mamba/value.hpp"

namespace mamba::builtins::concepts {

template <typename T>
concept Object = !Value<T> && StrConvertible<T> && requires(const T t) {
  // TODO: Fix by requiring { T::Init() } -> std::same_as<T>;
  { t.Repr() } -> std::same_as<types::Str>;
};

template <Object T, typename... Args>
T Init(Args&&... args) {
  // TODO: Fix by calling T::Init()
  return T(std::forward<Args>(args)...);
}

}  // namespace mamba::builtins::concepts
