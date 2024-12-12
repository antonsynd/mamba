#pragma once

#include <utility>

#include "mamba/builtins/__concepts/equatable.hpp"
#include "mamba/builtins/__types/bool.hpp"
#include "mamba/builtins/__types/object.hpp"
#include "mamba/builtins/__utils/log.hpp"

// Generic overload invoking __Eq__() dunder method
// template <mamba::builtins::details::EquatableObject T>
// bool operator==(const T& lhs, const T& rhs) {
//   mamba::builtins::details::Error() << "global equality";
//   return lhs.__Eq__(rhs);
// }

// If T doesn't have __Eq__(), then equality means identity
// bool operator==(const mamba::builtins::details::Object& lhs,
//                 const mamba::builtins::details::Object& rhs) {
//   mamba::builtins::details::Error() << "global equality id";
//   return lhs.__Id__() == rhs.__Id__();
// }

// Specialization of != if __Ne__() is defined
template <mamba::builtins::details::InequatableObject T>
bool operator!=(const T& lhs, const T& rhs) {
  mamba::builtins::details::Error() << "global inequality inequatable";
  return lhs.__Ne__(rhs);
}

// Fallback to inverse of == if __Ne__() is not defined
// bool operator!=(const mamba::builtins::details::Object& lhs,
//                 const mamba::builtins::details::Object& rhs) {
//   mamba::builtins::details::Error() << "global inequality for all";
//   return !::operator==(lhs, rhs);
// }

// IWYU pragma: private
