#pragma once

#include <algorithm>
#include <concepts>
#include <initializer_list>
#include <iostream>
#include <iterator>
#include <limits>
#include <optional>
#include <utility>
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

  static constexpr auto kEndIndex = std::numeric_limits<Int>::min();

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
    v_.reserve(elements.size());

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
    v_.reserve(v_.size() + other.v_.size());

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
    const auto end_index = v_.size();

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
  /// @code list[i:j:k]
  List<T> Slice(Int start = 0, Int end = kEndIndex, Int step = 1) const {
    List<T> res;

    auto slice_params_opt = TryGetNormalizedSliceParams(start, end, step);

    if (!slice_params_opt) {
      return res;
    }

    const auto size_t_start = slice_params_opt->start;
    const auto size_t_end = slice_params_opt->end;
    const auto size_t_step = slice_params_opt->step;

    // Simple range copy
    if (size_t_step == 1) {
      res.v_.reserve(size_t_end - size_t_start);

      // Need to recalculate in case reserve() invalidated the pre-calculated
      // iterators
      const auto start_it = v_.begin() + size_t_start;
      const auto end_it = v_.begin() + size_t_end;

      std::copy(start_it, end_it, std::back_inserter(res.v_));

      return res;
    }

    // Stepped range copy
    res.v_.reserve(
        GetNumberOfElementsInSlice(size_t_start, size_t_end, size_t_step));

    // Need to recalculate in case reserve() invalidated the pre-calculated
    // iterators
    const auto start_it = v_.begin() + size_t_start;
    const auto end_it = v_.begin() + size_t_end;

    size_t i = 0;

    std::copy_if(start_it, end_it, std::back_inserter(res.v_),
                 [&i, size_t_step](const auto) -> bool {
                   return i++ % size_t_step == 0;
                 });

    return res;
  }

#if __cplusplus >= 202302L
  List<T> operator[](Int start = 0, Int end = kEndIndex, Int step = 1) const {
    return Slice(start, end, step);
  }
#endif  // __cplusplus >= 202302L

  /// @brief Deletes the elements in the given slice. See Slice() for the
  /// behavior of the parameters.
  /// @code del list[i:j(:k)]
  void DeleteSlice(Int start = 0, Int end = kEndIndex, Int step = 1) {
    auto slice_params_opt = TryGetNormalizedSliceParams(start, end, step);

    if (!slice_params_opt) {
      return;
    }

    const auto [size_t_start, size_t_end, size_t_step, start_it, _] =
        *std::move(slice_params_opt);

    size_t i = 0;

    v_.erase(
        std::remove_if(
            start_it, v_.end(),
            [&i, size_t_start, size_t_end, size_t_step](const auto) -> bool {
              const auto remove =
                  i + size_t_start < size_t_end && i % size_t_step == 0;
              ++i;
              return remove;
            }),
        v_.end());
  }

  /// @brief Replaces the given slice with the elements of @p other. If @p step
  /// is not 1, then the length of @p other must be equal to the length of the
  /// slice, otherwise a ValueError will be thrown.
  /// @code list[i:j:k] = other
  void ReplaceSlice(const List<T>& other,
                    Int start = 0,
                    Int end = kEndIndex,
                    Int step = 1) {
    auto slice_params_opt = TryGetNormalizedSliceParams(start, end, step);

    if (!slice_params_opt) {
      return;
    }

    // Single step case, replace all in the range
    if (step == 1) {
      ReplaceSliceSingleStep(other, *std::move(slice_params_opt));
    } else {
      ReplaceSliceMultiStep(other, *std::move(slice_params_opt));
    }
  }

  /// @brief Returns the index of @p elem in the list, starting the search from
  /// @p start. If @p elem does not exist in the list, then throws ValueError.
  /// If @p start is negative, it is clamped to 0. If @p start is greater than
  /// the last index in the list, then it throws ValueError.
  /// @code list.index(i, (j))
  Int Index(T elem, Int start = 0) const {
    return Index(elem, start, v_.size());
  }

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
  /// @code list.insert(idx, x)
  void Insert(Int idx, T elem) {}

  /// @todo
  /// @code list.pop(idx)
  value Pop(Int idx = -1) {}

  /// @brief Removes the first occurrence of @p elem from the list. Elements
  /// are shifted to make the list contiguous. If the list is empty or
  /// @p elem does not occur in the list, throws ValueError.
  /// @code list.remove(elem)
  void Remove(const T& elem) {
    if (v_.empty()) {
      throw ValueError("List.Remove(x): x not in list");
    }

    auto it = std::find(v_.begin(), v_.end(), elem);

    if (it == v_.end()) {
      throw ValueError("List.Remove(x): x not in list");
    }

    v_.erase(it);
  }

  /// @brief Reverse the list in place.
  /// @code reverse(list)
  void Reverse() {
    if (v_.empty()) {
      return;
    }

    std::reverse(v_.begin(), v_.end());
  }

  /// @todo
  /// @code sort(list, key, reverse)
  void Sort(void* key, Bool reverse = false) {}

  /// @code list.__iter__()
  Iterator<List<T>> Iter() {
    return details::ListIterator(v_.cbegin(), v_.cend());
  }

  /// @code bool(list)
  Bool AsBool() const { return !v_.empty(); }

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
  size_t ClampIndex(Int idx) const {
    if (idx < 0) {
      return 0;
    } else if (idx > v_.size()) {
      return v_.size();
    }

    return static_cast<size_t>(idx);
  }

  size_t GetNumberOfElementsInSlice(size_t start,
                                    size_t end,
                                    size_t step) const {
    // Efficient ceil division (from ChatGPT)
    const auto length = end - start;
    return (length + step - 1) / step;
  }

  std::optional<size_t> TryGetNormalizedIndex(Int idx) const {
    if (idx < 0) {
      idx += v_.size();
    }

    if (idx < 0 || idx >= v_.size()) {
      return std::nullopt;
    }

    return static_cast<size_t>(idx);
  }

  Bool IsIndexOutOfBounds(Int idx) const {
    return !!TryGetNormalizedIndex(idx);
  }

  iterator GetIterator(size_t idx) { return v_.begin() + idx; }

  const_iterator GetIterator(size_t idx) const { return v_.cbegin() + idx; }

  std::optional<std::pair<size_t, size_t>>
  TryGetNormalizedSliceIndices(Int start, Int end, Int step) const {
    // Zero step is invalid
    if (step == 0) {
      throw ValueError("slice step cannot be zero");
    }

    // Negative step is no-op
    if (step < 0) {
      return std::nullopt;
    }

    start = TryGetNormalizedIndex(start).value_or(0);

    if (end == kEndIndex) {
      end = v_.size();
    } else {
      end = TryGetNormalizedIndex(end).value_or(v_.size());
    }

    // Start beyond end is no-op
    if (start >= end) {
      return std::nullopt;
    }

    return std::make_pair(start, end);
  }

  template <typename It>
  struct SliceParams {
    size_t start;
    size_t end;
    size_t step;
    It start_it;
    It end_it;
  };

  std::optional<SliceParams<const_iterator>>
  TryGetNormalizedSliceParams(Int start, Int end, Int step) const {
    const auto indices_opt = TryGetNormalizedSliceIndices(start, end, step);

    if (!indices_opt) {
      return std::nullopt;
    }

    const auto size_t_start = indices_opt->first;
    const auto size_t_end = indices_opt->second;

    return SliceParams<const_iterator>{
        size_t_start, size_t_end, static_cast<size_t>(step),
        GetIterator(size_t_start), GetIterator(size_t_end)};
  }

  std::optional<SliceParams<iterator>> TryGetNormalizedSliceParams(Int start,
                                                                   Int end,
                                                                   Int step) {
    const auto indices_opt = TryGetNormalizedSliceIndices(start, end, step);

    if (!indices_opt) {
      return std::nullopt;
    }

    const auto size_t_start = indices_opt->first;
    const auto size_t_end = indices_opt->second;

    return SliceParams<iterator>{
        size_t_start, size_t_end, static_cast<size_t>(step),
        GetIterator(size_t_start), GetIterator(size_t_end)};
  }

  void ReplaceSliceSingleStep(const List<T>& other,
                              SliceParams<iterator> slice_params) {
    const auto start_it = std::move(slice_params.start_it);
    const auto start = slice_params.start;
    const auto end = slice_params.end;

    const auto num_old_elems = GetNumberOfElementsInSlice(start, end, 1);
    const auto num_new_elems = other.v_.size();

    if (num_old_elems < num_new_elems) {
      ReplaceSliceSingleStepExpanding(other, start, num_old_elems,
                                      num_new_elems);
    } else if (num_old_elems > num_new_elems) {
      ReplaceSliceSingleStepReducing(other, start_it, num_old_elems,
                                     num_new_elems);
    } else {
      // Trivial case, replace 1-to-1
      std::copy(other.v_.begin(), other.v_.end(), start_it);
    }
  }

  void ReplaceSliceSingleStepExpanding(const List<T>& other,
                                       size_t start,
                                       size_t num_old_elems,
                                       size_t num_new_elems) {
    const auto num_extra_elems = num_new_elems - num_old_elems;
    v_.resize(v_.size() + num_extra_elems);

    // Recalculate the start iterator in case the resize() call
    // invalidated it
    const auto start_it = v_.begin() + start;

    // Shift elements from the starting position to make room for the
    // incoming ones
    std::shift_right(start_it, v_.end(), num_extra_elems);

    // Copy into the desired range
    std::copy(other.v_.begin(), other.v_.end(), start_it);
  }

  void ReplaceSliceSingleStepReducing(const List<T>& other,
                                      iterator start_it,
                                      size_t num_old_elems,
                                      size_t num_new_elems) {
    const auto num_elems_to_remove = num_old_elems - num_new_elems;

    // Copy into desired range
    start_it = std::copy(other.v_.begin(), other.v_.end(), start_it);
    const auto end_it = start_it + num_elems_to_remove;

    // Erase leftover elements
    v_.erase(start_it, end_it);
  }

  void ReplaceSliceMultiStep(const List<T>& other,
                             SliceParams<iterator> slice_params) {
    const auto [start, end, step, start_it, end_it] = std::move(slice_params);
    const auto num_old_elems = GetNumberOfElementsInSlice(start, end, step);

    if (other.v_.size() != num_old_elems) {
      throw ValueError(
          "ValueError: attempt to assign sequence of size {} to extended slice "
          "of size {}");
    }

    (void)start_it;
    (void)end_it;
    (void)other;
  }

  void Print() const {
    std::cout << "[ ";

    if (!v_.empty()) {
      auto last = v_.size() - 1;
      for (size_t i = 0; i < last; ++i) {
        std::cout << v_[i] << ", ";
      }

      std::cout << v_[last];
    }
    std::cout << " ]" << std::endl;
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
