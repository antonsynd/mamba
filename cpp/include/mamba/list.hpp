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
  using iterator = std::vector<T>::iterator;
  using const_iterator = std::vector<T>::const_iterator;

 public:
  using value = T;
  using reference = value&;
  using const_reference = const value&;

  /// @brief Creates an empty list.
  /// @code list()
  List() = default;

  /// @brief Creates a list with the same elements as @p it. Value types
  /// are copied.
  /// @code list(Iterable)
  template <typename I>
    requires concepts::Iterable<I>
  List(const I& it) {}

  /// @brief Creates a list with the provided variadic arguments.
  /// @code list(...)
  template <typename... Args>
  List(T elem, Args... rest) {
    Append(elem);
    Append(rest...);
  }

  /// @brief Creates a list from an initializer list (list literal).
  /// @code [...]
  List(std::initializer_list<T> elements) {
    std::copy(elements.begin(), elements.end(), std::back_inserter(v_));
  }

  /// @brief Appends @p elem to the end of the list.
  /// @code list.append(elem)
  void Append(T elem) { v_.emplace_back(elem); }

  /// @brief Appends @p elem and @p rest to the end of the list.
  /// @code list.append(...)
  template <typename... Args>
  void Append(T elem, Args... rest) {
    static_assert((std::is_same<T, Args>::value && ...),
                  "All elements must be of the same type.");
    Append(elem);
    Append(rest...);
  }

  /// @brief Returns whether @p elem is in the list. O(n).
  /// @code elem in list
  bool In(T elem) const {
    return std::find(v_.cbegin(), v_.cend(), elem) != v_.cend();
  }

  /// @brief Clears the elements of the list.
  /// @code list.clear()
  void Clear() { v_.clear(); }

  /// @brief Creates a shallow copy of the list.
  /// @code list.copy()
  List<T> Copy() const { return *this; }

  /// @brief Extends this list with the elements of @p other.
  /// @todo Fix to not assume list
  /// @code list.extend(Iterable)
  template <typename I>
    requires concepts::Iterable<I>
  void Extend(const I& other) {
    std::copy(other.v_.cbegin(), other.v_.cend(), std::back_inserter(v_));
  }

  /// @brief Extends this list with the elements of @p other.
  /// @code list += other
  void operator+=(const List<T>& other) { this->Extend(other); }

  /// @brief Concatenates this list with @p other.
  /// @code list + other
  List<T> operator+(const List<T>& other) const {
    List<T> res = *this;

    res.Extend(other);

    return res;
  }

  /// @brief Returns a copy of this list with its elements repeated @p i times.
  /// @code list * i
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

  /// @brief Repeats this list's elements @p i - 1 times.
  /// @code list *= i
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

  /// @brief Returns the element at index @p idx. If the index is out of range,
  /// throws IndexError. @p idx supports negative indices counting from the
  /// last elements.
  /// @code list[idx] (= elem)
  reference operator[](Int idx) {
    const auto idx_opt = TryGetNormalizedIndex(idx);

    if (!idx_opt) {
      throw IndexError("list index out of range");
    }

    return v_[*idx_opt];
  }

  const_reference operator[](Int idx) const {
    const auto idx_opt = TryGetNormalizedIndex(idx);

    if (!idx_opt) {
      throw IndexError("list index out of range");
    }

    return v_[*idx_opt];
  }

  /// @brief Returns the number of elements in the list.
  /// @code len(list)
  Int Len() const { return v_.size(); }

  /// @brief Returns the smallest element in the list. If the list is empty,
  /// throws ValueError.
  /// @code min(list)
  value Min() const {
    if (v_.empty()) {
      throw ValueError("Min() arg is an empty sequence");
    }

    return *std::min_element(v_.cbegin(), v_.cend());
  }

  /// @brief Returns the biggest element in the list. If the list is empty,
  /// throws ValueError.
  /// @code max(list)
  value Max() const {
    if (v_.empty()) {
      throw ValueError("Max() arg is an empty sequence");
    }

    return *std::max_element(v_.cbegin(), v_.cend());
  }

  /// @brief Returns the number of times @p elem is present in the list.
  /// @code list.count(x)
  Int Count(T elem) const {
    return std::count_if(v_.cbegin(), v_.cend(),
                         [elem](T val) { return val == elem; });
  }

  /// @brief Returns the elements in the list such that the elements' indices
  /// satify @p start <= idx < @p end, with @p step indices between the
  /// elements. If @p start >= @p end, then the returned list is empty.
  /// If @p step is negative, then the returned list is empty. If @p step is
  /// 0, then this throws ValueError.
  /// @code list[i:j(:k)]
  List<T> Slice(Int start, Int end, Int step = 1) const {
    List<T> res;

    if (step == 0) {
      throw ValueError("slice step cannot be zero");
    }

    // Negative step is empty list
    if (step < 0) {
      return res;
    }

    start = TryGetNormalizedIndex(start).value_or(0);
    end = TryGetNormalizedIndex(end).value_or(v_.size());

    // Empty list
    if (start >= end) {
      return res;
    }

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
  List<T> operator[](Int start, Int end, Int step = 1) const {
    return Slice(start, end, step);
  }
#endif  // __cplusplus >= 202302L

  /// @code list[i:j(:k)] = other
  void SliceReplace(const List<T>& other, Int start, Int end, Int step = 1) {
    //
  }

  /// @brief Returns the index of @p elem in the list, starting the search from
  /// @p start. If @p elem does not exist in the list, then throws ValueError.
  /// If @p start is negative, it is clamped to 0. If @p start is greater than
  /// the last index in the list, then it throws ValueError.
  /// @code list.index(i, (j))
  Int Index(T elem, Int start = 0) const { return Index(elem, start, Len()); }

  /// @brief Returns the index of @p elem in the list, starting the search from
  /// @p start and ending at @p end. If @p elem does not exist in the list,
  /// then throws ValueError. If @p start or @p end are negative, they are
  /// clamped to 0. If @p start is greater than the last index in the list,
  /// then it throws ValueError. If @p end is greater than the last index in
  /// the list, it is clamped to the length of the list.
  /// @code list.index(i, j, k)
  Int Index(T elem, Int start, Int end) const {
    end = ClampIndex(end);

    for (Int idx = ClampIndex(start); idx < end; ++idx) {
      if (v_[idx] == elem) {
        return idx;
      }
    }

    throw ValueError("{elem} is not in list");
  }

  /// @todo
  /// @code list.insert()
  void Insert(Int idx, T elem) {}

  /// @todo
  /// @code list.pop()
  void Pop(Int idx = -1) {}

  /// @todo
  /// @code list.remove()
  void Remove(T elem) {}

  /// @code reverse(list)
  void Reverse() { std::reverse(v_.begin(), v_.end()); }

  /// @todo
  /// @code sort(list, key, reverse)
  void Sort(void* key, Bool reverse = false) {}

  /// @code list.__iter__()
  Iterator<List<T>> Iter() {
    return details::ListIterator(v_.cbegin(), v_.cend());
  }

  /// @code bool(list)
  Bool AsBool() const { return Len() > 0; }

  /// @brief
  /// @code list == other
  template <typename U>
  Bool Eq(const U&) const {
    return false;
  }

  /// @brief
  /// @code list === other
  template <>
  Bool Eq(const List<T>& other) const {
    return v_ == other.v_;
  }

 private:
  Int ClampIndex(Int idx) const {
    if (idx < 0) {
      return 0;
    } else if (idx > Len()) {
      return Len();
    }

    return idx;
  }

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

  iterator GetIterator(Int idx) {
    if (idx < 0) {
      return v_.end() + idx;
    }

    return v_.begin() + idx;
  }

  const_iterator GetIterator(Int idx) const {
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
  ListIterator(std::vector<T>::iterator it, std::vector<T>::iterator end)
      : it_(std::move(it)), end_(std::move(end)) {}

  Iterator<T> Iter() const override { return *this; }

  T Next() override {
    if (it_ == end_) {
      throw StopIteration("end of iterator");
    }

    return *it_++;
  }

 private:
  std::vector<T>::iterator it_;
  std::vector<T>::iterator end_;
};

}  // namespace details

}  // namespace mamba::builtins::types
