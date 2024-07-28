#pragma once

#include <algorithm>
#include <concepts>
#include <initializer_list>
#include <iterator>
#include <optional>
#include <vector>

#include "mamba/concepts.hpp"
#include "mamba/error.hpp"
#include "mamba/iterable.hpp"
#include "mamba/iterator.hpp"
#include "mamba/not_null.hpp"
#include "mamba/value.hpp"

namespace mamba::builtins::types {
namespace details {

// Forward declaration
template <typename T>
class ListIterator;

}  // namespace details

template <concepts::Value T>
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
  template <typename I>
    requires concepts::Iterable<I>
  List(const I& it) {}

  /// @brief Target is `list(...)`
  template <typename... Args>
  List(T elem, Args... rest) {
    Append(elem);
    Append(rest...);
  }

  List(std::initializer_list<T> elements) {
    std::copy(elements.begin(), elements.end(), std::back_inserter(v_));
  }

  void Append(T elem) { v_.emplace_back(elem); }

  template <typename... Args>
  void Append(T elem, Args... rest) {
    static_assert((std::is_same<T, Args>::value && ...),
                  "All elements must be of the same type.");
    Append(elem);
    Append(rest...);
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
  template <typename I>
    requires concepts::Iterable<I>
  void Extend(const I& other) {
    std::copy(other.v_.cbegin(), other.v_.cend(), std::back_inserter(v_));
  }

  void operator+=(const List<T>& other) { this->Extend(other); }

  /// @brief Target of `x + y`
  List<T> operator+(const List<T>& other) const {
    List<T> res = *this;

    res.Extend(other);

    return res;
  }

  /// @brief Target of `x * n`
  List<T> operator*(Int i) const {
    List<T> res;

    if (i <= 0) {
      return res;
    }

    res.v_.reserve(v_.size() * i);

    for (; i > 0; --i) {
      res.Extend(*this);
    }

    return res;
  }

  /// @brief Target of `x *= n`
  void operator*=(Int i) {
    if (i == 1) {
      return;
    } else if (i < 1) {
      v_.clear();
      return;
    }

    v_.reserve(v_.size() * i);
    const auto end_index = Len();

    for (; i > 1; --i) {
      for (size_t j = 0; j < end_index; ++j) {
        v_.emplace_back(v_[j]);
      }
    }
  }

  /// @brief Target of `x[i] = j`
  reference_t operator[](Int idx) {
    const auto idx_opt = TryGetNormalizedIndex(idx);

    if (!idx_opt) {
      throw IndexError("list index out of range");
    }

    return v_[*idx_opt];
  }

  /// @brief Target of `x[i]`
  value_t operator[](Int idx) const {
    const auto idx_opt = TryGetNormalizedIndex(idx);

    if (!idx_opt) {
      throw IndexError("list index out of range");
    }

    return v_[*idx_opt];
  }

  /// @brief Target of `len(x)`
  Int Len() const { return v_.size(); }

  /// @brief Target of `min(list)`
  value_t Min() const {
    if (v_.empty()) {
      throw ValueError("Min() arg is an empty sequence");
    }

    return *std::min_element(v_.begin(), v_.end());
  }

  /// @brief Target of `max(list)`
  value_t Max() const {
    if (v_.empty()) {
      throw ValueError("Max() arg is an empty sequence");
    }

    return *std::max_element(v_.begin(), v_.end());
  }

  /// @brief Target of `list.count(x)`
  Int Count(T elem) const {
    return std::count_if(v_.cbegin(), v_.cend(),
                         [elem](T val) { return val == elem; });
  }

  /// @brief Target of `x[i:j(:k)]`
  List<T> Slice(Int start, Int end, Int step = 1) const {
    List<T> res;

    if (step == 0) {
      throw ValueError("slice step cannot be zero");
    }

    // 0 length case, and negative step
    if (end == start || step < 0) {
      return res;
    }

    start = TryGetNormalizedIndex(start).value_or(0);
    end = TryGetNormalizedIndex(end).value_or(v_.size());

    auto start_it = GetIterator(start);
    const auto end_it = GetIterator(end);

    // Simple range copy
    if (step == 1) {
      res.v_.reserve(end - start);
      std::copy(start_it, end_it, std::back_inserter(res.v_));

      return res;
    }

    // Stepped range copy
    // Efficient ceil division (from ChatGPT)
    const Int length = end - start;
    res.v_.reserve((length + step - 1) / step);

    for (Int i = 0; i < length; i += step) {
      res.v_.push_back(*start_it);

      start_it += step;
    }

    return res;
  }

#if __cplusplus >= 202302L
  /// @brief Target `list[i:j(:k)]`
  List<T> operator[](Int start, Int end, Int step = 1) const {
    return Slice(start, end, step);
  }
#endif  // __cplusplus >= 202302L

  /// @todo
  /// Use a proxy to accept the incoming slice
  void ReplaceSlice(const List<T>& other, Int start, Int end, Int step = 1) {}

  /// @brief Target of `x.index(i, (j))`
  Int Index(T elem, Int start = 0) const {
    if (IsIndexOutOfBounds(start)) {
      // TODO: format string
      throw ValueError("{elem} is not in list");
    }

    const auto& it = std::find(GetIterator(start), v_.end(), elem);

    if (it == v_.end()) {
      // TODO: format string
      throw ValueError("{elem} is not in list");
    }

    // Base case
    if (it == v_.begin()) {
      return 0;
    }

    return static_cast<Int>(std::distance(v_.begin(), it));
  }

  /// @brief Target of `x.index(i, j, k)`
  Int Index(T elem, Int start, Int end) const {
    if (IsIndexOutOfBounds(start) || IsIndexOutOfBounds(end)) {
      // TODO: format string
      throw ValueError("{elem} is not in list");
    }

    const auto& it = std::find(GetIterator(start), GetIterator(end), elem);

    if (it == v_.end()) {
      // TODO: format string
      throw ValueError("{elem} is not in list");
    }

    // Base case
    if (it == v_.begin()) {
      return 0;
    }

    return static_cast<Int>(std::distance(v_.begin(), it));
  }

  /// @brief Target of `list.insert()`
  /// @todo
  void Insert(Int idx, T elem) {}

  /// @brief Target of `list.pop()`
  /// @todo
  void Pop(Int idx = -1) {}

  /// @brief Target of `list.remove()`
  /// @todo
  void Remove(T elem) {}

  /// @brief Target of `reverse(x)`
  void Reverse() { std::reverse(v_.begin(), v_.end()); }

  /// @brief Target of `list.__iter__()`
  Iterator<List<T>> Iter() { return details::ListIterator(*this); }

  /// @brief Traget of `bool(list)`
  Bool AsBool() const { return Len() > 0; }

  template <typename U>
  Bool Eq(const U&) const {
    return false;
  }

  template <>
  Bool Eq(const List<T>& other) const {
    return v_ == other.v_;
  }

 private:
  std::optional<Int> TryGetNormalizedIndex(Int idx) const {
    if (idx < 0) {
      idx += v_.size();
    }

    if (idx < 0 || idx >= v_.size()) {
      return std::nullopt;
    }

    return idx;
  }

  Bool IsIndexOutOfBounds(Int idx) const {
    return !!TryGetNormalizedIndex(idx);
  }

  iterator_t GetIterator(Int idx) {
    if (idx < 0) {
      return v_.end() + idx;
    }

    return v_.begin() + idx;
  }

  const_iterator_t GetIterator(Int idx) const {
    if (idx < 0) {
      return v_.cend() + idx;
    }

    return v_.cbegin() + idx;
  }

  std::vector<T> v_;
};

namespace details {

template <typename T>
class ListIterator : public Iterator<List<T>> {
 public:
  ListIterator(List<T>& l) : l_(&l) {}

  Iterator<T> Iter() const override { return *this; }
  T Next() {}

 private:
  not_null<List<T>> l_;
};

}  // namespace details

}  // namespace mamba::builtins::types
