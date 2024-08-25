#pragma once

#include <memory>
#include <stdexcept>
#include <type_traits>
#include <utility>

// From https://github.com/microsoft/GSL/blob/main/include/gsl/pointers
namespace gsl {
namespace details {

template <typename T, typename = void>
struct is_comparable_to_nullptr : std::false_type {};

template <typename T>
struct is_comparable_to_nullptr<
    T,
    std::enable_if_t<std::is_convertible<decltype(std::declval<T>() != nullptr),
                                         bool>::value>> : std::true_type {};

// Resolves to the more efficient of `const T` or `const T&`, in the context of
// returning a const-qualified value of type T.
//
// Copied from cppfront's implementation of the CppCoreGuidelines F.16
// (https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#Rf-in)
template <typename T>
using value_or_reference_return_t =
    std::conditional_t<sizeof(T) < 2 * sizeof(void*) &&
                           std::is_trivially_copy_constructible<T>::value,
                       const T,
                       const T&>;

}  // namespace details

template <typename T>
class not_null {
 public:
  static_assert(details::is_comparable_to_nullptr<T>::value,
                "T cannot be compared to nullptr.");

  template <typename U,
            typename = std::enable_if_t<std::is_convertible<U, T>::value>>
  constexpr not_null(U&& u) noexcept(
      std::is_nothrow_move_constructible<T>::value)
      : ptr_(std::forward<U>(u)) {
    if (!ptr_) {
      throw std::runtime_error("pointer cannot be nullptr");
    }
  }

  template <
      typename = std::enable_if_t<!std::is_same<std::nullptr_t, T>::value>>
  constexpr not_null(T u) noexcept(std::is_nothrow_move_constructible<T>::value)
      : ptr_(std::move(u)) {
    if (!ptr_) {
      throw std::runtime_error("pointer cannot be nullptr");
    }
  }

  template <typename U,
            typename = std::enable_if_t<std::is_convertible<U, T>::value>>
  constexpr not_null(const not_null<U>& other) noexcept(
      std::is_nothrow_move_constructible<T>::value)
      : not_null(other.get()) {}

  not_null(const not_null& other) = default;
  not_null& operator=(const not_null& other) = default;
  constexpr details::value_or_reference_return_t<T> get() const
      noexcept(noexcept(details::value_or_reference_return_t<T>{
          std::declval<T&>()})) {
    return ptr_;
  }

  constexpr operator T() const { return get(); }
  constexpr decltype(auto) operator->() const { return get(); }
  constexpr decltype(auto) operator*() const { return *get(); }

  // prevents compilation when someone attempts to assign a null pointer
  // constant
  not_null(std::nullptr_t) = delete;
  not_null& operator=(std::nullptr_t) = delete;

  // unwanted operators...pointers only point to single objects!
  not_null& operator++() = delete;
  not_null& operator--() = delete;
  not_null operator++(int) = delete;
  not_null operator--(int) = delete;
  not_null& operator+=(std::ptrdiff_t) = delete;
  not_null& operator-=(std::ptrdiff_t) = delete;
  void operator[](std::ptrdiff_t) const = delete;

 private:
  T ptr_;
};

}  // namespace gsl

namespace mamba::builtins::__utils {

template <typename T>
using not_null = gsl::not_null<T>;

}  // namespace mamba::builtins::__utils
