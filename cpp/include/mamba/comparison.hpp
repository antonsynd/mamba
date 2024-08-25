#pragma once

#include <concepts>

#include "mamba/concepts/object.hpp"
#include "mamba/concepts/value.hpp"
#include "mamba/memory/handle.hpp"
#include "mamba/types/bool.hpp"

namespace mamba::builtins {
namespace operators {

template <concepts::EquatableValue T, concepts::EquatableValue U>
types::Bool Eq(const T lhs, const U rhs) {
  return lhs == rhs;
}

template <concepts::LessThanComparableValue T,
          concepts::LessThanComparableValue U>
types::Bool Lt(const T lhs, const U rhs) {
  return lhs < rhs;
}

template <concepts::LessThanComparableValue T,
          concepts::LessThanComparableValue U>
types::Bool LtEq(const T lhs, const U rhs) {
  return lhs <= rhs;
}

template <concepts::GreaterThanComparableValue T,
          concepts::GreaterThanComparableValue U>
types::Bool Gt(const T lhs, const U rhs) {
  return lhs > rhs;
}

template <concepts::GreaterThanComparableValue T,
          concepts::GreaterThanComparableValue U>
types::Bool GtEq(const T lhs, const U rhs) {
  return lhs >= rhs;
}

template <concepts::EquatableObject T, concepts::EquatableObject U>
types::Bool Eq(const T& lhs, const U& rhs) {
  return lhs.Eq(rhs);
}

template <concepts::LessThanComparableObject T,
          concepts::LessThanComparableObject U>
types::Bool Lt(const T& lhs, const U& rhs) {
  return lhs.Lt(rhs);
}

template <concepts::LessThanComparableObject T,
          concepts::LessThanComparableObject U>
types::Bool LtEq(const T& lhs, const U& rhs) {
  return lhs.Lt(rhs) || lhs.Eq(rhs);
}

template <concepts::GreaterThanComparableObject T,
          concepts::GreaterThanComparableObject U>
types::Bool Gt(const T& lhs, const U& rhs) {
  return lhs.Gt(rhs);
}

template <concepts::GreaterThanComparableObject T,
          concepts::GreaterThanComparableObject U>
types::Bool GtEq(const T& lhs, const U& rhs) {
  return lhs.Gt(rhs) || lhs.Eq(rhs);
}

template <concepts::EquatableObject T, concepts::EquatableObject U>
types::Bool Eq(const memory::handle_t<T>& lhs, const memory::handle_t<U>& rhs) {
  return lhs->Eq(*rhs);
}

template <concepts::LessThanComparableObject T,
          concepts::LessThanComparableObject U>
types::Bool Lt(const memory::handle_t<T>& lhs, const memory::handle_t<U>& rhs) {
  return lhs->Lt(*rhs);
}

template <concepts::LessThanComparableObject T,
          concepts::LessThanComparableObject U>
types::Bool LtEq(const memory::handle_t<T>& lhs,
                 const memory::handle_t<U>& rhs) {
  return lhs->Lt(*rhs) || lhs->Eq(*rhs);
}

template <concepts::GreaterThanComparableObject T,
          concepts::GreaterThanComparableObject U>
types::Bool Gt(const memory::handle_t<T>& lhs, const memory::handle_t<U>& rhs) {
  return lhs->Gt(*rhs);
}

template <concepts::LessThanComparableObject T,
          concepts::LessThanComparableObject U>
types::Bool GtEq(const memory::handle_t<T>& lhs,
                 const memory::handle_t<U>& rhs) {
  return lhs->Gt(*rhs) || lhs->Eq(*rhs);
}

}  // namespace operators

// For C++ syntax
template <concepts::EquatableObject T, concepts::EquatableObject U>
bool operator==(const T& lhs, const U& rhs) {
  return operators::Eq(lhs, rhs);
}

template <concepts::EquatableObject T, concepts::EquatableObject U>
bool operator!=(const T& lhs, const U& rhs) {
  return !operators::Eq(lhs, rhs);
}

template <concepts::LessThanComparableObject T,
          concepts::LessThanComparableObject U>
bool operator<(const T& lhs, const U& rhs) {
  return operators::Lt(lhs, rhs);
}

template <concepts::LessThanComparableObject T,
          concepts::LessThanComparableObject U>
bool operator<=(const T& lhs, const U& rhs) {
  return operators::LtEq(lhs, rhs);
}

template <concepts::GreaterThanComparableObject T,
          concepts::GreaterThanComparableObject U>
bool operator>(const T& lhs, const U& rhs) {
  return operators::Gt(lhs, rhs);
}

template <concepts::GreaterThanComparableObject T,
          concepts::GreaterThanComparableObject U>
bool operator>=(const T& lhs, const U& rhs) {
  return operators::GtEq(lhs, rhs);
}

template <concepts::EquatableObject T, concepts::EquatableObject U>
bool operator==(const memory::handle_t<T>& lhs,
                const memory::handle_t<U>& rhs) {
  return operators::Eq(*lhs, *rhs);
}

template <concepts::EquatableObject T, concepts::EquatableObject U>
bool operator!=(const memory::handle_t<T>& lhs,
                const memory::handle_t<U>& rhs) {
  return !operators::Eq(*lhs, *rhs);
}

template <concepts::LessThanComparableObject T,
          concepts::LessThanComparableObject U>
bool operator<(const memory::handle_t<T>& lhs, const memory::handle_t<U>& rhs) {
  return operators::Lt(*lhs, *rhs);
}

template <concepts::LessThanComparableObject T,
          concepts::LessThanComparableObject U>
bool operator<=(const memory::handle_t<T>& lhs,
                const memory::handle_t<U>& rhs) {
  return operators::LtEq(*lhs, *rhs);
}

template <concepts::GreaterThanComparableObject T,
          concepts::GreaterThanComparableObject U>
bool operator>(const memory::handle_t<T>& lhs, const memory::handle_t<U>& rhs) {
  return operators::Gt(*lhs, *rhs);
}

template <concepts::GreaterThanComparableObject T,
          concepts::GreaterThanComparableObject U>
bool operator>=(const memory::handle_t<T>& lhs,
                const memory::handle_t<U>& rhs) {
  return operators::GtEq(*lhs, *rhs);
}

}  // namespace mamba::builtins
