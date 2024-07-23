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
  bool In(T elem) const {
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
  List<T> operator+(const List<T>& other) const {
    List<T> res = *this;

    res.extend(other);

    return res;
  }

  /// @brief Target of `x * n`
  List<T> operator*(int_t i) const {
    List<T> res;
    res.v_.reserve(v_.size() * i);

    for (; i > 0; --i) {
      res.extend(*this);
    }

    return res;
  }

  /// @brief Target of `x *= n`
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
  reference_t operator[](int_t idx) { return v_.at[GetNormalizedIndex(idx)]; }

  /// @brief Target of `x[i]`
  value_t operator[](int_t idx) const { return v_[GetNormalizedIndex(idx)]; }

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

    start = GetNormalizedIndex(start);
    end = GetNormalizedIndex(end);

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

#if __cplusplus >= 202302L
  /// @brief Target `list[i:j(:k)]`
  List<T> operator[](int_t start, int_t end, int_t step = 1) const {
    return Slice(start, end, step);
  }
#endif  // __cplusplus >= 202302L

  /// @todo
  /// Use a proxy to accept the incoming slice
  void ReplaceSlice(const List<T>& other,
                    int_t start,
                    int_t end,
                    int_t step = 1) {}

  /// @brief Target of `x.index(i, (j))`
  int_t Index(T elem, int_t start = 0) const {
    if (IsIndexOutOfBounds(start)) {
      // TODO: format string
      throw ValueError("{elem} is not in list");
    }

    const auto& it = std::find(GetNormalizedIterator(start), v_.end(), elem);

    if (it == v_.end()) {
      // TODO: format string
      throw ValueError("{elem} is not in list");
    }

    // Base case
    if (it == v_.begin()) {
      return 0;
    }

    return static_cast<int_t>(std::distance(v_.begin(), it));
  }

  /// @brief Target of `x.index(i, j, k)`
  int_t Index(T elem, int_t start, int_t end) const {
    if (IsIndexOutOfBounds(start) || IsIndexOutOfBounds(end)) {
      // TODO: format string
      throw ValueError("{elem} is not in list");
    }

    const auto& it = std::find(GetNormalizedIterator(start),
                               GetNormalizedIterator(end), elem);

    if (it == v_.end()) {
      // TODO: format string
      throw ValueError("{elem} is not in list");
    }

    // Base case
    if (it == v_.begin()) {
      return 0;
    }

    return static_cast<int_t>(std::distance(v_.begin(), it));
  }

  /// @brief Target of `list.insert()`
  /// @todo
  void Insert(int_t idx, T elem) {}

  /// @brief Target of `list.pop()`
  /// @todo
  void Pop(int_t i = -1) {}

  /// @brief Target of `list.remove()`
  /// @todo
  void Remove(T elem) {}

  /// @brief Target of `reverse(x)`
  void Reverse() { std::reverse(v_.begin(), v_.end()); }

 private:
  int_t GetNormalizedIndex(int_t idx) const {
    if (idx < 0) {
      return v_.size() + idx;
    }

    return idx;
  }

  bool_t IsIndexOutOfBounds(int_t idx) const {
    idx = GetNormalizedIndex(idx);

    return idx < 0 || idx >= v_.size();
  }

  iterator_t GetNormalizedIterator(int_i idx) {
    if (GetNormalizedIndex(idx) != idx) {
      throw std::logic_error("idx must be normalized");
    }

    if (idx < 0) {
      return v_.end() + idx;
    }

    return v_.start() + idx;
  }

  const_iterator_t GetNormalizedIterator(int_i idx) const {
    if (GetNormalizedIndex(idx) != idx) {
      throw std::logic_error("idx must be normalized");
    }

    if (idx < 0) {
      return v_.end() + idx;
    }

    return v_.start() + idx;
  }

  std::vector<T> v_;
};

template <typename T>
using list_t = List<T>;

}  // namespace mamba::builtins
