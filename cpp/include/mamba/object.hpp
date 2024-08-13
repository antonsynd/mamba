#pragma once

#include <concepts>
#include <type_traits>

#include "mamba/value.hpp"

namespace mamba::builtins::concepts {

template <typename T>
concept Object = !Value<T> && requires {
  typename std::enable_if_t<std::is_function_v<decltype(T::Init)>>;
};

template <Object T, typename... Args>
T Init(Args&&... args) {
  return T::Init(std::forward<Args>(args)...);
}

}  // namespace mamba::builtins::concepts
