#pragma once

#include <algorithm>
#include <concepts>
#include <initializer_list>
#include <iterator>
#include <limits>
#include <memory>
#include <optional>
#include <sstream>
#include <utility>
#include <vector>

#include "mamba/builtins/__concepts/orderable.hpp"
#include "mamba/builtins/__conversion/str.hpp"
#include "mamba/builtins/__memory/args.hpp"
#include "mamba/builtins/__types/big_int.hpp"
#include "mamba/builtins/__types/int.hpp"
#include "mamba/builtins/__types/object.hpp"
#include "mamba/builtins/__types/str.hpp"
#include "mamba/builtins/error.hpp"
#include "mamba/builtins/iteration.hpp"
#include "mamba/builtins/repr.hpp"

namespace mamba::builtins {
namespace details {

// Forward declaration
template <typename T>
class ListIterator;

template <typename F, typename K>
concept ListSortKey = requires(const F& key_func, __memory::Const<K> k) {
  { key_func(k) } -> __concepts::LessThanComparable;
};

}  // namespace details

template <__concepts::LessThanComparable T>
class List : public __types::Object {
 public:
  using value_type = T;

  /// @note Mamba-specific
  using self = List<value_type>;
  using storage = std::vector<value_type>;

  using reference = value_type&;
  using const_reference = const value_type&;

  using iterator = storage::iterator;
  using const_iterator = storage::const_iterator;

  static constexpr auto kEndIndex = std::numeric_limits<__types::Int>::min();

  /// @brief Creates an empty list.
  /// @code list()
  List() : data_(std::make_shared<Data>()) {}

  /// @brief Creates a list with the same elements as @p it. Value types
  /// are copied.
  /// @code list(Iterable)
  template <typename It>
    requires __concepts::IterableOf<It, value_type>
  List(const It& iterable) : data_(std::make_shared<Data>()) {
    bool no_stop_iteration = true;
    auto it = iterable.__Iter__();

    while (no_stop_iteration) {
      try {
        Append(Next(*it));
      } catch (StopIteration) {
        no_stop_iteration = false;
        break;
      }
    }
  }

  /// @brief Creates a list from an initializer list (list literal).
  /// @code [...]
  List(std::initializer_list<value_type> elements)
      : data_(std::make_shared<Data>()) {
    data_->v_.reserve(elements.size());

    if constexpr (__concepts::Value<value_type>) {
      std::copy(elements.begin(), elements.end(),
                std::back_inserter(data_->v_));
    } else {
      std::copy(std::make_move_iterator(elements.begin()),
                std::make_move_iterator(elements.end()),
                std::back_inserter(data_->v_));
    }
  }

  /// @brief Creates a list with the provided variadic arguments.
  /// @code list(...)
  template <typename... Args>
    requires(std::same_as<std::decay_t<Args>, value_type> && ...)
  List(Args&&... rest) : data_(std::make_shared<Data>()) {
    Append(std::forward<Args>(rest)...);
  }

  /// @brief Generic constructor forwarding arguments to actual constructor
  /// methods.
  /// @code List.__init__()
  template <typename... Args>
  static self __Init__(Args&&... args) {
    return self(std::forward<Args>(args)...);
  }

  /// @brief Appends variadic args @p rest to the end of the list.
  /// @code list.append(...)
  template <typename... Args>
  void Append(Args&&... rest) {
    (data_->v_.emplace_back(std::forward<Args>(rest)), ...);
  }

  /// @brief Returns whether @p elem is in the list. O(n).
  /// @code elem in list
  __types::Bool __Contains__(__memory::Const<value_type> elem) const {
    return std::find(data_->v_.cbegin(), data_->v_.cend(), elem) !=
           data_->v_.cend();
  }

  /// @brief Clears the elements of the list.
  /// @code list.clear()
  void Clear() { data_->v_.clear(); }

  /// @brief Creates a shallow copy of the list.
  /// @code list.copy()
  self Copy() const {
    // Invoke copy constructor with shallow copy of internal data.
    return *this;
  }

  /// @brief Extends this list with the elements of @p other.
  /// @code list.extend(list)
  void Extend(const self& other) {
    data_->v_.reserve(data_->v_.size() + other->data_->v_.size());

    std::copy(other->data_->v_.cbegin(), other->data_->v_.cend(),
              std::back_inserter(data_->v_));
  }

  /// @brief Extends this list with the elements of @p other.
  /// @code list += other
  void operator+=(const self& other) { Extend(other); }

  /// @brief Concatenates this list with @p other returning the result as a new
  /// list.
  /// @code list + other
  self operator+(const self& other) const {
    self res;

    res.Extend(*this);
    res.Extend(other);

    return res;
  }

  /// @brief Returns a copy of this list with its elements repeated @p i times.
  /// @code list * i
  self operator*(__types::Int i) const {
    self res;

    if (i <= 0) {
      return res;
    }

    res.data_->v_.reserve(data_->v_.size() * i);

    for (; i > 0; --i) {
      res.Extend(*this);
    }

    return res;
  }

  /// @brief Repeats this list's elements @p i - 1 times.
  /// @code list *= i
  void operator*=(__types::Int i) {
    if (i == 1) {
      return;
    } else if (i < 1) {
      data_->v_.clear();
      return;
    }

    data_->v_.reserve(data_->v_.size() * i);
    const auto end_index = data_->v_.size();

    for (; i > 1; --i) {
      for (size_t j = 0; j < end_index; ++j) {
        data_->v_.emplace_back(data_->v_[j]);
      }
    }
  }

  /// @brief Returns the element at index @p idx. If the index is out of range,
  /// throws IndexError. @p idx supports negative indices counting from the
  /// last elements.
  /// @code list[idx] (= elem)
  reference operator[](__types::Int idx) {
    const auto idx_opt = TryGetNormalizedIndex(idx);

    if (!idx_opt) {
      throw IndexError("list index out of range");
    }

    return data_->v_[*idx_opt];
  }

  const_reference operator[](__types::Int idx) const {
    const auto idx_opt = TryGetNormalizedIndex(idx);

    if (!idx_opt) {
      throw IndexError("list index out of range");
    }

    return data_->v_[*idx_opt];
  }

  /// @brief Returns the number of elements in the list.
  /// @code len(list)
  __types::Int __Len__() const { return data_->v_.size(); }

  /// @brief Returns the smallest element in the list. If the list is empty,
  /// throws ValueError.
  /// @code min(list)
  value_type Min() const {
    if (data_->v_.empty()) {
      throw ValueError("Min() arg is an empty sequence");
    }

    // if constexpr (__concepts::Value<value_type>) {
    return *std::min_element(data_->v_.cbegin(), data_->v_.cend());
    // } else {
    //   return *std::min_element(
    //       data_->v_.cbegin(), data_->v_.cend(),
    //       [](const auto a, const auto b) { return a < b; });
    // }
  }

  /// @brief Returns the biggest element in the list. If the list is empty,
  /// throws ValueError.
  /// @code max(list)
  value_type Max() const {
    if (data_->v_.empty()) {
      throw ValueError("Max() arg is an empty sequence");
    }

    // if constexpr (__concepts::Value<value_type>) {
    return *std::max_element(data_->v_.cbegin(), data_->v_.cend());
    // } else {
    //   return *std::max_element(
    //       data_->v_.cbegin(), data_->v_.cend(),
    //       [](const auto a, const auto b) { return a < *b; });
    // }
  }

  /// @brief Returns the number of times @p elem is present in the list.
  /// @code list.count(x)
  __types::Int Count(__memory::Const<value_type> elem) const {
    return std::count_if(
        data_->v_.cbegin(), data_->v_.cend(),
        [elem](__memory::Const<value_type> val) { return val == elem; });
  }

  /// @brief Returns the elements in the list such that the elements' indices
  /// satify @p start <= idx < @p end, with @p step indices between the
  /// elements. If @p start >= @p end, then the returned list is empty.
  /// If @p step is negative, then the returned list is empty. If @p step is
  /// 0, then this throws ValueError.
  /// @code list[i:j:k]
  self Slice(__types::Int start = 0,
             __types::Int end = kEndIndex,
             __types::Int step = 1) const {
    self res;

    auto slice_params_opt = TryGetNormalizedSliceParams(start, end, step);

    if (!slice_params_opt) {
      return res;
    }

    const auto size_t_start = slice_params_opt->start;
    const auto size_t_end = slice_params_opt->end;
    const auto size_t_step = slice_params_opt->step;

    // Simple range copy
    if (size_t_step == 1) {
      res.data_->v_.reserve(size_t_end - size_t_start);

      // Need to recalculate in case reserve() invalidated the pre-calculated
      // iterators
      const auto start_it = data_->v_.begin() + size_t_start;
      const auto end_it = data_->v_.begin() + size_t_end;

      std::copy(start_it, end_it, std::back_inserter(res.data_->v_));

      return res;
    }

    // Stepped range copy
    res.data_->v_.reserve(
        GetNumberOfElementsInSlice(size_t_start, size_t_end, size_t_step));

    // Need to recalculate in case reserve() invalidated the pre-calculated
    // iterators
    const auto start_it = data_->v_.begin() + size_t_start;
    const auto end_it = data_->v_.begin() + size_t_end;

    size_t i = 0;

    std::copy_if(start_it, end_it, std::back_inserter(res.data_->v_),
                 [&i, size_t_step](const auto) -> bool {
                   return i++ % size_t_step == 0;
                 });

    return res;
  }

#if __cplusplus >= 202302L
  self operator[](__types::Int start = 0,
                  __types::Int end = kEndIndex,
                  __types::Int step = 1) const {
    return Slice(start, end, step);
  }
#endif  // __cplusplus >= 202302L

  /// @brief Deletes the elements in the given slice. See Slice() for the
  /// behavior of the parameters.
  /// @code del list[i:j(:k)]
  void DeleteSlice(__types::Int start = 0,
                   __types::Int end = kEndIndex,
                   __types::Int step = 1) {
    auto slice_params_opt = TryGetNormalizedSliceParams(start, end, step);

    if (!slice_params_opt) {
      return;
    }

    const auto [size_t_start, size_t_end, size_t_step, start_it, _] =
        *std::move(slice_params_opt);

    size_t i = 0;

    const auto erase_from_it = std::remove_if(
        start_it, data_->v_.end(),
        [&i, size_t_start, size_t_end, size_t_step](const auto) -> bool {
          const auto remove =
              i + size_t_start < size_t_end && i % size_t_step == 0;
          ++i;
          return remove;
        });

    data_->v_.erase(erase_from_it, data_->v_.end());
  }

  /// @brief Replaces the given slice with the elements of @p other. If @p step
  /// is not 1, then the length of @p other must be equal to the length of the
  /// slice, otherwise a ValueError will be thrown.
  /// @code list[i:j:k] = other
  void ReplaceSlice(const self& other,
                    __types::Int start = 0,
                    __types::Int end = kEndIndex,
                    __types::Int step = 1) {
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
  __types::Int Index(__memory::Const<value_type> elem,
                     __types::Int start = 0) const {
    return Index(elem, start, data_->v_.size());
  }

  /// @brief Returns the index of @p elem in the list, starting the search from
  /// @p start and ending at @p end. If @p elem does not exist in the list,
  /// then throws ValueError. If @p start or @p end are negative, they are
  /// clamped to 0. If @p start is greater than the last index in the list,
  /// then it throws ValueError. If @p end is greater than the last index in
  /// the list, it is clamped to the length of the list.
  /// @code list.index(i, j, k)
  __types::Int Index(__memory::Const<value_type> elem,
                     __types::Int start,
                     __types::Int end) const {
    end = ClampIndex(end);

    for (__types::Int idx = ClampIndex(start); idx < end; ++idx) {
      if (data_->v_[idx] == elem) {
        return idx;
      }
    }

    throw ValueError("{elem} is not in list");
  }

  /// @brief Inserts @p elem so that it becomes the element at @p idx, pushing
  /// any element at that position to the right. @p idx is clamped to the
  /// length of the list.
  /// @code list.insert(idx, x)
  void Insert(__types::Int idx, __memory::Mut<value_type> elem) {
    const auto size_t_idx = NormalizeOrClampIndex(idx);

    if (size_t_idx == data_->v_.size()) {
      data_->v_.emplace_back(elem);
    } else {
      const auto it = GetIterator(size_t_idx);
      data_->v_.insert(it, elem);
    }
  }

  /// @brief Removes the element at @p idx and returns it. If @p idx is out of
  /// bounds, then throws IndexError.
  /// @code list.pop(idx)
  value_type Pop(__types::Int idx = -1) {
    const auto idx_opt = TryGetNormalizedIndex(idx);

    if (!idx_opt) {
      throw IndexError("pop index out of range");
    }

    const auto size_t_idx = *idx_opt;
    const auto it = GetIterator(size_t_idx);
    auto elem = *it;

    if (size_t_idx == data_->v_.size() - 1) {
      // Trivial case, pop from the back
      data_->v_.pop_back();
    } else {
      // Erase an element from the start or middle
      data_->v_.erase(it);
    }

    return elem;
  }

  /// @brief Removes the first occurrence of @p elem from the list. Elements
  /// are shifted to make the list contiguous. If the list is empty or
  /// @p elem does not occur in the list, throws ValueError.
  /// @code list.remove(elem)
  void Remove(__memory::Const<value_type> elem) {
    if (data_->v_.empty()) {
      throw ValueError("List.Remove(x): x not in list");
    }

    auto it = data_->v_.end();

    // if constexpr (__concepts::Value<value_type>) {
    it = std::find(data_->v_.begin(), data_->v_.end(), elem);
    // } else {
    //   it = std::find_if(data_->v_.begin(), data_->v_.end(),
    //                     [&elem](const auto v) { return elem == v; });
    // }

    if (it == data_->v_.end()) {
      throw ValueError("List.Remove(x): x not in list");
    }

    data_->v_.erase(it);
  }

  /// @brief Reverse the list in place.
  /// @code reverse(list)
  void Reverse() {
    if (data_->v_.empty()) {
      return;
    }

    std::reverse(data_->v_.begin(), data_->v_.end());
  }

  /// @brief Sorts the list in-place, with the order of equal-comparing
  /// elements guaranteed to be preserved. Each element is compared using
  /// the less-than operator.
  /// @code sort(list, reverse)
  void Sort(__types::Bool reverse = false) {
    if (data_->v_.empty()) {
      return;
    }

    if (reverse) {
      // We sort with the inverse of the comparison to make sure the sort
      // is stable, rather than reverse the results afterwards
      std::sort(
          data_->v_.begin(), data_->v_.end(),
          [](const auto a, const auto b) { return !(a < b || !(b < a)); });
    } else {
      std::sort(data_->v_.begin(), data_->v_.end(),
                [](const auto a, const auto b) { return a < b; });
    }
  }

  /// @brief Sorts the list in-place, with the order of equal-comparing
  /// elements guaranteed to be preserved. Every element is transformed via
  /// @p key before it is compared using the less-than operator.
  /// @code sort(list, key, reverse)
  template <typename K>
    requires details::ListSortKey<K, value_type>
  void Sort(const K& key, __types::Bool reverse = false) {
    if (data_->v_.empty()) {
      return;
    }

    if (reverse) {
      // We sort with the inverse of the comparison to make sure the sort
      // is stable, rather than reverse the results afterwards
      std::sort(data_->v_.begin(), data_->v_.end(),
                [&key](const auto a, const auto b) {
                  const auto ka = key(a);
                  const auto kb = key(b);
                  return !(ka < kb || !(kb < ka));
                });
    } else {
      std::sort(data_->v_.begin(), data_->v_.end(),
                [&key](const auto a, const auto b) { return key(a) < key(b); });
    }
  }

  /// @brief Returns an iterator to this list.
  /// @code list.__iter__()
  std::unique_ptr<Iterator<value_type>> __Iter__() const {
    return std::make_unique<details::ListIterator<value_type>>(
        data_->v_.begin(), data_->v_.end());
  }

  /// @brief Native support for C++ for..in loops.
  iterator begin() { return data_->v_.begin(); }
  iterator end() { return data_->v_.end(); }
  const_iterator begin() const { return data_->v_.cbegin(); }
  const_iterator end() const { return data_->v_.cend(); }
  const_iterator cbegin() const { return data_->v_.cbegin(); }
  const_iterator cend() const { return data_->v_.cend(); }

  /// @code bool(list)
  __types::Bool __Bool__() const override { return !data_->v_.empty(); }

  /// @brief Returns true if this and @p other contain the same elements, and
  /// false otherwise.
  /// @code list == other
  __types::Bool __Eq__(const self& other) const {
    if constexpr (__concepts::Value<value_type>) {
      // Value elements are checked for equality
      return std::equal(data_->v_.begin(), data_->v_.end(),
                        other.data_->v_.begin(), other.data_->v_.end(),
                        [](const auto a, const auto b) { return a == b; });
    } else {
      // Non-value elements are checked for identity
      return std::equal(
          data_->v_.begin(), data_->v_.end(), other.data_->v_.begin(),
          other.data_->v_.end(),
          [](const auto a, const auto b) { return a.__Id__() == b.__Id__(); });
    }
  }

  /// @brief Returns the string representation of the list.
  /// @code str(list)
  __types::Str __Str__() const override {
    std::ostringstream oss;

    oss << "[";

    if (!data_->v_.empty()) {
      const auto last = data_->v_.size() - 1;

      for (size_t i = 0; i < last; ++i) {
        oss << __conversion::Str(data_->v_[i]) << ", ";
      }

      oss << __conversion::Str(data_->v_[last]);
    }

    oss << "]";

    return oss.str();
  }

  /// @brief Returns the representation of the list.
  /// @code repr(list)
  __types::Str __Repr__() const override {
    std::ostringstream oss;

    oss << "[";

    if (!data_->v_.empty()) {
      const auto last = data_->v_.size() - 1;

      for (size_t i = 0; i < last; ++i) {
        oss << Repr(data_->v_[i]) << ", ";
      }

      oss << Repr(data_->v_[last]);
    }

    oss << "]";

    return oss.str();
  }

  __types::BigInt __Id__() const override {
    return reinterpret_cast<__types::BigInt>(data_.get());
  }

 private:
  size_t ClampIndex(__types::Int idx) const {
    if (idx < 0) {
      return 0;
    } else if (idx > data_->v_.size()) {
      return data_->v_.size();
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

  std::optional<size_t> TryGetNormalizedIndex(__types::Int idx) const {
    if (idx < 0) {
      idx += data_->v_.size();
    }

    if (idx < 0 || idx >= data_->v_.size()) {
      return std::nullopt;
    }

    return static_cast<size_t>(idx);
  }

  size_t NormalizeOrClampIndex(__types::Int idx) const {
    return TryGetNormalizedIndex(idx).value_or(ClampIndex(idx));
  }

  iterator GetIterator(size_t idx) { return data_->v_.begin() + idx; }

  const_iterator GetIterator(size_t idx) const {
    return data_->v_.cbegin() + idx;
  }

  std::optional<std::pair<size_t, size_t>> TryGetNormalizedSliceIndices(
      __types::Int start,
      __types::Int end,
      __types::Int step) const {
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
      end = data_->v_.size();
    } else {
      end = TryGetNormalizedIndex(end).value_or(data_->v_.size());
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

  std::optional<SliceParams<const_iterator>> TryGetNormalizedSliceParams(
      __types::Int start,
      __types::Int end,
      __types::Int step) const {
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

  std::optional<SliceParams<iterator>> TryGetNormalizedSliceParams(
      __types::Int start,
      __types::Int end,
      __types::Int step) {
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

  void ReplaceSliceSingleStep(const self& other,
                              SliceParams<iterator> slice_params) {
    const auto start_it = std::move(slice_params.start_it);
    const auto start = slice_params.start;
    const auto end = slice_params.end;

    const auto num_old_elems = end - start;
    const auto num_new_elems = other.data_->v_.size();

    if (num_old_elems < num_new_elems) {
      ReplaceSliceSingleStepExpanding(other, start, num_old_elems,
                                      num_new_elems);
    } else if (num_old_elems > num_new_elems) {
      ReplaceSliceSingleStepReducing(other, start_it, num_old_elems,
                                     num_new_elems);
    } else {
      // Trivial case, replace 1-to-1
      std::copy(other.data_->v_.begin(), other.data_->v_.end(), start_it);
    }
  }

  void ReplaceSliceSingleStepExpanding(const self& other,
                                       size_t start,
                                       size_t num_old_elems,
                                       size_t num_new_elems) {
    const auto num_extra_elems = num_new_elems - num_old_elems;
    data_->v_.resize(data_->v_.size() + num_extra_elems);

    // Recalculate the start iterator in case the resize() call
    // invalidated it
    const auto start_it = data_->v_.begin() + start;

    // Shift elements from the starting position to make room for the
    // incoming ones
    std::shift_right(start_it, data_->v_.end(), num_extra_elems);

    // Copy into the desired range
    std::copy(other.data_->v_.begin(), other.data_->v_.end(), start_it);
  }

  void ReplaceSliceSingleStepReducing(const self& other,
                                      iterator start_it,
                                      size_t num_old_elems,
                                      size_t num_new_elems) {
    const auto num_elems_to_remove = num_old_elems - num_new_elems;

    // Copy into desired range
    start_it =
        std::copy(other.data_->v_.begin(), other.data_->v_.end(), start_it);
    const auto end_it = start_it + num_elems_to_remove;

    // Erase leftover elements
    data_->v_.erase(start_it, end_it);
  }

  void ReplaceSliceMultiStep(const self& other,
                             SliceParams<iterator> slice_params) {
    const auto [start, end, step, start_it, end_it] = std::move(slice_params);
    const auto num_old_elems = GetNumberOfElementsInSlice(start, end, step);

    if (other.data_->v_.size() != num_old_elems) {
      throw ValueError(
          "ValueError: attempt to assign sequence of size {} to extended "
          "slice "
          "of size {}");
    }

    size_t idx = 0;
    auto other_it = other.data_->v_.begin();
    const auto other_end = other.data_->v_.end();

    std::for_each(start_it, end_it,
                  [&idx, step, &other_it, &other_end](auto& elem) {
                    if (other_it == other_end) {
                      // Shouldn't happen, but here as a fail-safe
                      return;
                    }

                    if (idx % step == 0) {
                      elem = *other_it;
                      ++other_it;
                    }

                    ++idx;
                  });
  }

  class Data {
   public:
    storage v_;
  };

  std::shared_ptr<Data> data_;
};

namespace details {

template <typename T>
class ListIterator : public Iterator<T> {
 public:
  using value_type = T;
  using iterator = List<value_type>::iterator;

  /// @brief Mamba-specific
  using self = ListIterator<value_type>;
  using base = Iterator<value_type>;

  ListIterator(iterator it, iterator end)
      : data_(std::make_shared<Data>(std::move(it), std::move(end))) {}

  ~ListIterator() override = default;

  /// @brief Generic constructor forwarding arguments to actual constructor
  /// methods.
  /// @code ListIterator.__init__()
  template <typename... Args>
  static self __Init__(Args&&... args) {
    return self(std::forward<Args>(args)...);
  }

  std::unique_ptr<Iterator<value_type>> __Iter__() const override {
    // Return shallow copy of this
    return std::make_unique<self>(*this);
  }

  value_type __Next__() override {
    if (data_->it_ == data_->end_) {
      throw StopIteration("end of iterator");
    }

    return *data_->it_++;
  }

  __types::Str __Repr__() const override { return "ListIterator"; }

  __types::Bool __Eq__(const self& other) const {
    return data_->it_ == other.data_->it_ && data_->end_ == other.data_->end_;
  }

  __types::Bool __Eq__(const base& other) const override {
    if (const auto* other_ptr = dynamic_cast<const self*>(&other)) {
      return __Eq__(*other_ptr);
    }

    return false;
  }

  __types::BigInt __Id__() const override {
    return reinterpret_cast<__types::BigInt>(data_.get());
  }

  constexpr __types::Bool __Bool__() const override { return true; }

 private:
  class Data {
   public:
    Data(iterator it, iterator end)
        : it_(std::move(it)), end_(std::move(end)) {}

    iterator it_;
    iterator end_;
  };

  std::shared_ptr<Data> data_;
};

}  // namespace details

}  // namespace mamba::builtins
