#pragma once

#include <type_traits>

#include "mamba/bool.hpp"
#include "mamba/float.hpp"
#include "mamba/int.hpp"
#include "mamba/none.hpp"
#include "mamba/str.hpp"

namespace mamba::builtins::traits {

template <typename T>
struct is_value_type {
  static constexpr auto value = std::disjunction_v<std::is_same<T, int_t>,
                                                   std::is_same<T, float_t>,
                                                   std::is_same<T, bool_t>,
                                                   std::is_same<T, str_t>,
                                                   std::is_same<T, none_t>>;
};

template <typename T>
constexpr auto is_value_type_v = is_value_type<T>::value;

template <typename Iterable, typename Element>
struct is_iterable {
  /// @todo Also consider subclasses of list_t, and classes that implement
  /// Element& Iterable::iterator()
  static constexpr auto value =
      std::is_same_v<Iterable<Element>, list_t<Element>>;
};

template <typename Iterable, typename Element>
constexpr auto is_iterable_v = is_iterable<Iterable, Element>::value;

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
