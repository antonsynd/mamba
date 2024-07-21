#pragma once

#include <type_traits>
#include <utility>

#include "mamba/bool.hpp"
#include "mamba/float.hpp"
#include "mamba/int.hpp"
#include "mamba/str.hpp"
#include "mamba/traits.hpp"

namespace mamba::builtins {

bool_t as_bool(bool_t b) {
  return b;
}

bool_t as_bool(int_t i) {
  return i != 0;
}

bool_t as_bool(float_t f) {
  return f != 0;
}

bool_t as_bool(str_t s) {
  return !s.empty();
}

template <typename T, std::enable_if_t<traits::implements_as_bool_v<T>>>
bool_t as_bool(const T& t) {
  return T.as_bool();
}

str_t as_str(int_t i) {
  return std::to_string(i);
}

str_t as_str(float_t f) {
  return std::to_string(f);
}

str_t as_str(bool_t f) {
  return std::to_string(f);
}

/// @note The return value is expected to be a new copy of @p s. Returning an
/// lvalue ref is not expected here. However, we can move a temporary if it
/// was passed in, hence the use of a forwarding reference.
str_t as_str(str_t&& s) {
  return std::forward<str_t>(s);
}

template <typename T, std::enable_if_t<traits::implements_as_str_v<T>>>
bool_t as_str(const T& t) {
  return T.as_str();
}

}  // namespace mamba::builtins
