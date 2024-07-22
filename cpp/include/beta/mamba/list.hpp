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
    return std::find(v_.cbegin(), v_.cend(), elem) != v_.end();
  }

  /// @brief Target of `list.clear()`
  void clear() { v_.clear(); }

  /// @brief Target of `list.copy()`
  List<T> copy() const { return *this; }

  /// @brief Target of `list.extend(Iterable)`
  /// @todo Fix to not assume list_t
  template <typename Iterable,
            std::enable_if_t<traits::is_iterable_v<Iterable, T>>>
  void extend(const Iterable<T>& other) {
    std::copy(other.cbegin(), other.cend(), std::back_inserter(v_));
  }

  void operator+=(const List<T>& other) { this->extend(other); }

  /// @brief Target of `x + y`
  List<T> operator+(const List<T>& other) {
    List<T> res = *this;

    res.extend(other);

    return res;
  }

  /// @brief Target of `x * n`
  List<T> operator*(int_t i) {
    List<T> res;
    res.v_.reserve(v_.size() * i);

    for (; i > 0; --i) {
      res.extend(*this);
    }

    return res;
  }

  void operator*=(int_t i) {
    if (i == 1) {
      return;
    } else if (i == 0) {
      clear();
    }

    v_.reserve(v_.length() * i);

    for (; i > 1; --i) {
      this->extend(*this);
    }
  }

  /// @todo Implement negative indices
  T& operator[](int_t idx) { return v_[idx]; }

  /// @todo Implement negative indices
  T operator[](int_t idx) const { return v_[idx]; }

  int_t len() const { return v_.size(); }

  /// @todo Actually implement
  T min() const { return v_.front(); }
  T max() const { return v_.front(); }

  int_t count(T elem) const {
    return std::count_if(v_.cbegin(), v_.cend(),
                         [](T val) { return val == elem; });
  }

  /// @brief Target of `x[i:j(:k)]`
  /// @todo
  List<T> slice(int_t start, int_t end, int_t step = 1) const { return *this; }

  /// @tood
  void replace_slice(const List<T>& other,
                     int_t start,
                     int_t end,
                     int_t step = 1) {}

  /// @brief Target of `x.index(i, (j, (k)))`
  /// @todo
  int_t index(T elem, int_t start = 0, int_t end = -1) const { return 0; }

  void insert(int_t idx, T elem) {}
  void pop(int_t i) {}
  void remove(T elem) {}
  void reverse() {}

 private:
  std::vector<T> v_;
};

template <typename T>
using list_t = List<T>;

}  // namespace mamba::builtins
