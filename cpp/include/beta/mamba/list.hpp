#pragma once

#include <algorithm>
#include <iterator>
#include <type_traits>
#include <vector>

#include "mamba/error.hpp"
#include "mamba/traits.hpp"

namespace mamba::builtins {

template <typename T, std::enable_if_t<traits::is_value_type_v<T>>>
class List {
 private:
  using iterator_t = std::vector<T>::iterator;
  using const_iterator_t = std::vector<T>::const_iterator;

 public:
  using value_t = T;
  using reference_t = value_t&;
  using const_reference_t = const value_t&;

  /// @brief Target is `list()`
  List() = default;

  /// @brief Target is `list(Iterable)`
  template <typename Iterable,
            std::enable_if_t<traits::is_iterable_v<Iterable, T>>>
  List(const Iterable<T>& it) {}

  /// @brief Target is `list(...)`
  template <typename T, typename... Args>
  List(T elem, Args... rest) {
    Append(elem);
    Append(rest...);
  }

  template <typename T>
  void Append(T elem) {
    v_.emplace_back(elem);
  }

  template <typename T, typename... Args>
  void Append(T elem, Args... rest) {
    static_assert((std::is_same<T, Args>::value && ...),
                  "All elements must be of the same type.");
    append(elem);
    append(rest...);
  }

  /// @brief Target of `x in y`
  bool Contains(T elem) const {
    return std::find(v_.cbegin(), v_.cend(), elem) != v_.end();
  }

  /// @brief Target of `list.clear()`
  void Clear() { v_.clear(); }

  /// @brief Target of `list.copy()`
  List<T> Copy() const { return *this; }

  /// @brief Target of `list.extend(Iterable)`
  /// @todo Fix to not assume list_t
  template <typename Iterable,
            std::enable_if_t<traits::is_iterable_v<Iterable, T>>>
  void Extend(const Iterable<T>& other) {
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

  /// @brief Target of `x[i] = j`
  reference_t operator[](int_t idx) { return v_.at[NormalizeIndex(idx)]; }

  /// @brief Target of `x[i]`
  value_t operator[](int_t idx) const { return v_[NormalizeIndex(idx)]; }

  /// @brief Target of `len(x)`
  int_t Len() const { return v_.size(); }

  /// @brief Target of `list.min()`
  value_t Min() const { return *std::min_element(v_.begin(), v_.end()); }

  /// @brief Target of `list.max()`
  value_t Max() const { return *std::max_element(v_.begin(), v_.end()); }

  /// @brief Target of `list.count(x)`
  int_t Count(T elem) const {
    return std::count_if(v_.cbegin(), v_.cend(),
                         [](T val) { return val == elem; });
  }

  /// @brief Target of `x[i:j(:k)]`
  List<T> Slice(int_t start, int_t end, int_t step = 1) const {
    List<T> res;

    if (step == 0) {
      throw ValueError("slice step cannot be zero");
    }

    // 0 length case, and negative step
    if (end == start || step < 0) {
      return res;
    }

    start = NormalizeIndex(start);
    end = NormalizeIndex(end);

    const auto start_it = GetNormalizedIterator(start);
    const auto end_it = GetNormalizedIterator(start);

    // Simple range copy
    if (step == 1) {
      res.v_.reserve(end - start);
      std::copy(start_it, end_it, std::back_inserter(res.v_));

      return res;
    }

    // Stepped range copy
    // Efficient ceil division (from ChatGPT)
    const int_t length = end - start;
    res.v_.reserve((length + step - 1) / step);

    for (int_t i = 0; i < length; i += step) {
      // Note: this expression is a no-op on the first iteration
      start_it += i;

      res.v_.push_back(*start_it);
    }

    return res;
  }

  /// @todo
  /// Use a proxy to accept the incoming slice
  void ReplaceSlice(const List<T>& other,
                    int_t start,
                    int_t end,
                    int_t step = 1) {}

  /// @brief Target of `x.index(i, (j, (k)))`
  /// @todo
  int_t Index(T elem, int_t start = 0) const { return 0; }
  int_t Index(T elem, int_t start = 0, int_t end) const { return 0; }

  void Insert(int_t idx, T elem) {}
  void Pop(int_t i) {}
  void Remove(T elem) {}

  /// @brief Target of `reverse(x)`
  void Reverse() { std::reverse(v_.begin(), v_.end()); }

 private:
  int_t NormalizeIndex(int_t i) const {
    if (i < 0) {
      return v_.size() + i;
    }

    return i;
  }

  iterator_t GetNormalizedIterator(int_i i) {
    if (i < 0) {
      return v_.end() + i;
    }

    return v_.start() + i;
  }

  const_iterator_t NormalizedIterator(int_i i) const {
    if (i < 0) {
      return v_.end() + i;
    }

    return v_.start() + i;
  }

  std::vector<T> v_;
};

template <typename T>
using list_t = List<T>;

}  // namespace mamba::builtins
