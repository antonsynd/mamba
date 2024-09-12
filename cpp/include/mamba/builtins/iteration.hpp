#pragma once

#include <concepts>
#include <memory>
#include <type_traits>

#include "mamba/__concepts/entity.hpp"
#include "mamba/__memory/managed.hpp"
#include "mamba/builtins/__types/object.hpp"

namespace mamba::builtins {

template <__concepts::Entity T>
class Iterator : public builtins::__types::Object {
 public:
  using element = T;
  using value = __memory::managed_t<element>;

  virtual ~Iterator() = default;

  virtual __memory::handle_t<Iterator<element>> Iter() = 0;
  virtual value Next() = 0;
};

namespace __concepts {

template <typename T, typename U>
concept TypedIterable = requires(T* iterable) {
  { iterable->Iter() } -> std::same_as<__memory::handle_t<Iterator<U>>>;
};

template <typename T>
concept Iterable = TypedIterable<T, typename T::element>;

}  // namespace __concepts

template <__concepts::Entity T>
__memory::managed_t<T> Next(Iterator<T>& it) {
  return it.Next();
}

template <__concepts::Entity T>
__memory::managed_t<T> Next(const __memory::handle_t<Iterator<T>>& it) {
  return Next(*it);
}

template <__concepts::Iterable T>
__memory::handle_t<Iterator<typename T::element>> Iter(T& it) {
  return it.Iter();
}

template <__concepts::Iterable T>
__memory::handle_t<Iterator<typename T::element>> Iter(
    const __memory::handle_t<T>& it) {
  return Iter(*it);
}

// template <__concepts::Iterable T>
// class CppIterator {
//  public:
//   /// @note Mamba-specific
//   using element = typename T::element;
//   using self = CppIterator<T>;
//   using iterator = __memory::handle_t<Iterator<element>>;

//   using value_type = __memory::managed_t<element>;

//   explicit CppIterator(T iterable) : at_end_(false), it_(iterable.Iter()) {}

//   self& operator++() {
//     try {
//       Next(*it_);
//     } catch (StopIteration) {
//       no_stop_iteration = false;
//     }

//     return *this;
//   }

//   self operator++(int) {
//     auto res = it;
//     this->operator++();

//     return res;
//   }

//   value_type operator*() { return *it_; }

//   bool operator==(const self& other) const {return }

//   self begin() const {
//     return *this;
//   }
//   self end() const {
//     auto res = *this;
//     res.at_end_ = true;
//   }

//  private:
//   bool at_end_;
//   iterator it_;
// };

}  // namespace mamba::builtins
