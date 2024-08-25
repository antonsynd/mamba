#pragma once

#include <concepts>

#include "mamba/__concepts/object.hpp"
#include "mamba/__concepts/value.hpp"
#include "mamba/__memory/handle.hpp"
#include "mamba/builtins/__types/bool.hpp"

namespace mamba::builtins {
namespace operators {

template <__concepts::EquatableValue T, __concepts::EquatableValue U>
__types::Bool Eq(const T lhs, const U rhs) {
  return lhs == rhs;
}

template <__concepts::LessThanComparableValue T,
          __concepts::LessThanComparableValue U>
__types::Bool Lt(const T lhs, const U rhs) {
  return lhs < rhs;
}

template <__concepts::LessThanComparableValue T,
          __concepts::LessThanComparableValue U>
__types::Bool LtEq(const T lhs, const U rhs) {
  return lhs <= rhs;
}

template <__concepts::GreaterThanComparableValue T,
          __concepts::GreaterThanComparableValue U>
__types::Bool Gt(const T lhs, const U rhs) {
  return lhs > rhs;
}

template <__concepts::GreaterThanComparableValue T,
          __concepts::GreaterThanComparableValue U>
__types::Bool GtEq(const T lhs, const U rhs) {
  return lhs >= rhs;
}

template <__concepts::EquatableObject T, __concepts::EquatableObject U>
__types::Bool Eq(const T& lhs, const U& rhs) {
  return lhs.Eq(rhs);
}

template <__concepts::LessThanComparableObject T,
          __concepts::LessThanComparableObject U>
__types::Bool Lt(const T& lhs, const U& rhs) {
  return lhs.Lt(rhs);
}

template <__concepts::LessThanComparableObject T,
          __concepts::LessThanComparableObject U>
__types::Bool LtEq(const T& lhs, const U& rhs) {
  return lhs.Lt(rhs) || lhs.Eq(rhs);
}

template <__concepts::GreaterThanComparableObject T,
          __concepts::GreaterThanComparableObject U>
__types::Bool Gt(const T& lhs, const U& rhs) {
  return lhs.Gt(rhs);
}

template <__concepts::GreaterThanComparableObject T,
          __concepts::GreaterThanComparableObject U>
__types::Bool GtEq(const T& lhs, const U& rhs) {
  return lhs.Gt(rhs) || lhs.Eq(rhs);
}

template <__concepts::EquatableObject T, __concepts::EquatableObject U>
__types::Bool Eq(const __memory::handle_t<T>& lhs,
                 const __memory::handle_t<U>& rhs) {
  return lhs->Eq(*rhs);
}

template <__concepts::LessThanComparableObject T,
          __concepts::LessThanComparableObject U>
__types::Bool Lt(const __memory::handle_t<T>& lhs,
                 const __memory::handle_t<U>& rhs) {
  return lhs->Lt(*rhs);
}

template <__concepts::LessThanComparableObject T,
          __concepts::LessThanComparableObject U>
__types::Bool LtEq(const __memory::handle_t<T>& lhs,
                   const __memory::handle_t<U>& rhs) {
  return lhs->Lt(*rhs) || lhs->Eq(*rhs);
}

template <__concepts::GreaterThanComparableObject T,
          __concepts::GreaterThanComparableObject U>
__types::Bool Gt(const __memory::handle_t<T>& lhs,
                 const __memory::handle_t<U>& rhs) {
  return lhs->Gt(*rhs);
}

template <__concepts::LessThanComparableObject T,
          __concepts::LessThanComparableObject U>
__types::Bool GtEq(const __memory::handle_t<T>& lhs,
                   const __memory::handle_t<U>& rhs) {
  return lhs->Gt(*rhs) || lhs->Eq(*rhs);
}

}  // namespace operators

// For C++ syntax
template <__concepts::EquatableObject T, __concepts::EquatableObject U>
bool operator==(const T& lhs, const U& rhs) {
  return operators::Eq(lhs, rhs);
}

template <__concepts::EquatableObject T, __concepts::EquatableObject U>
bool operator!=(const T& lhs, const U& rhs) {
  return !operators::Eq(lhs, rhs);
}

template <__concepts::LessThanComparableObject T,
          __concepts::LessThanComparableObject U>
bool operator<(const T& lhs, const U& rhs) {
  return operators::Lt(lhs, rhs);
}

template <__concepts::LessThanComparableObject T,
          __concepts::LessThanComparableObject U>
bool operator<=(const T& lhs, const U& rhs) {
  return operators::LtEq(lhs, rhs);
}

template <__concepts::GreaterThanComparableObject T,
          __concepts::GreaterThanComparableObject U>
bool operator>(const T& lhs, const U& rhs) {
  return operators::Gt(lhs, rhs);
}

template <__concepts::GreaterThanComparableObject T,
          __concepts::GreaterThanComparableObject U>
bool operator>=(const T& lhs, const U& rhs) {
  return operators::GtEq(lhs, rhs);
}

template <__concepts::EquatableObject T, __concepts::EquatableObject U>
bool operator==(const __memory::handle_t<T>& lhs,
                const __memory::handle_t<U>& rhs) {
  return operators::Eq(*lhs, *rhs);
}

template <__concepts::EquatableObject T, __concepts::EquatableObject U>
bool operator!=(const __memory::handle_t<T>& lhs,
                const __memory::handle_t<U>& rhs) {
  return !operators::Eq(*lhs, *rhs);
}

template <__concepts::LessThanComparableObject T,
          __concepts::LessThanComparableObject U>
bool operator<(const __memory::handle_t<T>& lhs,
               const __memory::handle_t<U>& rhs) {
  return operators::Lt(*lhs, *rhs);
}

template <__concepts::LessThanComparableObject T,
          __concepts::LessThanComparableObject U>
bool operator<=(const __memory::handle_t<T>& lhs,
                const __memory::handle_t<U>& rhs) {
  return operators::LtEq(*lhs, *rhs);
}

template <__concepts::GreaterThanComparableObject T,
          __concepts::GreaterThanComparableObject U>
bool operator>(const __memory::handle_t<T>& lhs,
               const __memory::handle_t<U>& rhs) {
  return operators::Gt(*lhs, *rhs);
}

template <__concepts::GreaterThanComparableObject T,
          __concepts::GreaterThanComparableObject U>
bool operator>=(const __memory::handle_t<T>& lhs,
                const __memory::handle_t<U>& rhs) {
  return operators::GtEq(*lhs, *rhs);
}

}  // namespace mamba::builtins
