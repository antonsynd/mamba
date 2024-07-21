#pragma once

#include <algorithm>
#include <iterator>
#include <type_traits>
#include <vector>

#include "mamba/traits.hpp"

namespace mamba::builtins {

template <typename T, std::enable_if_t<traits::is_value_type_v<T>>>
class List {
 public:
  /// @brief Target is `list()`
  List() = default;

  /// @brief Target is `list(Iterable)`
  template <typename Iterable,
            std::enable_if_t<traits::is_iterable_v<Iterable, T>>>
  List(const Iterable<T>& it) {}

  /// @brief Target is `list(...)`
  template <typename T, typename... Args>
  List(T elem, Args... rest) {
    append(elem);
    append(rest...);
  }

  template <typename T>
  void append(T elem) {
    v_.emplace_back(elem);
  }

  template <typename T, typename... Args>
  void append(T elem, Args... rest) {
    static_assert((std::is_same<T, Args>::value && ...),
                  "All elements must be of the same type.");
    append(elem);
    append(rest...);
  }

  /// @brief Target of `x in y`
  bool contains(T elem) const {
    return std::find(v_.begin(), v_.end(), elem) != v_.end();
  }

  /// @brief Target of `list.clear()`
  void clear() { v_.clear(); }

  /// @brief Target of `list.copy()`
  List<T> copy() { return *this; }

  /// @brief Target of `list.extend(Iterable)`
  /// @todo Fix to not assume list_t
  template <typename Iterable,
            std::enable_if_t<traits::is_iterable_v<Iterable, T>>>
  void extend(const Iterable<T>& other) {
    std::copy(other.begin(), other.end(), std::back_inserter(v_));
  }

  /// @brief Target of `x + y`
  List<T> operator+(const List<T>& other) {
    List<T> res;

    res.emplace
  }

 private:
  std::vector<T> v_;
};

template <typename T>
using list_t = List<T>;

}  // namespace mamba::builtins
