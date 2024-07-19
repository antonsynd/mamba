#pragma once

#include <type_traits>

#include "mamba/beta/bool.hpp"
#include "mamba/beta/str.hpp"

namespace mamba::builtins::traits {

template <typename T>
struct implements_as_bool {
  static constexpr auto value = std::conjunction_v<
      std::is_member_function_pointer<decltype(&T::as_bool)>,
      std::is_invocable_r<bool_t, decltype(&T::as_bool), T*>>;
};

template <typename T>
constexpr auto implements_as_bool_v = implements_as_bool<T>::value;

template <typename T>
struct implements_as_str {
  static constexpr auto value =
      std::conjunction_v<std::is_member_function_pointer<decltype(&T::as_str)>,
                         std::is_invocable_r<str_t, decltype(&T::as_str), T*>>;
};

template <typename T>
constexpr auto implements_as_str_v = implements_as_str<T>::value;

}  // namespace mamba::builtins::traits
