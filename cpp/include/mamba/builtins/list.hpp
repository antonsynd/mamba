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

#include "mamba/__concepts/comparable.hpp"
#include "mamba/__concepts/entity.hpp"
#include "mamba/__memory/handle.hpp"
#include "mamba/__memory/managed.hpp"
#include "mamba/__memory/read_only.hpp"
#include "mamba/builtins/__types/int.hpp"
#include "mamba/builtins/__types/str.hpp"
#include "mamba/builtins/as_str.hpp"
#include "mamba/builtins/comparators.hpp"
#include "mamba/builtins/error.hpp"
#include "mamba/builtins/iteration.hpp"
#include "mamba/builtins/repr.hpp"

namespace mamba::builtins {
namespace details {

// Forward declaration
template <__concepts::Entity T>
class ListIterator;

template <typename F, typename K>
concept ListSortKey = requires(const F& key_func, __memory::ReadOnly<K> k) {
  { key_func(k) } -> __concepts::LessThanComparable;
};

}  // namespace details

template <typename T>
  requires __concepts::Entity<T> && __concepts::LessThanComparable<T>
class List : public std::enable_shared_from_this<List<T>> {
 public:
  /// @note Mamba-specific
  using element = T;

  using value_type = __memory::managed_t<element>;
  using reference = value_type&;
  using const_reference = const value_type&;

  /// @note Mamba-specific
  using storage = std::vector<value_type>;

  using iterator = storage::iterator;
  using const_iterator = storage::const_iterator;

  /// @note Mamba-specific
  using self = List<element>;
  using handle = __memory::handle_t<self>;

  static constexpr auto kEndIndex = std::numeric_limits<__types::Int>::min();

  /// @brief Creates an empty list.
  /// @code list()
  List() {}

  /// @brief Creates a list with the same elements as @p it. Value types
  /// are copied.
  /// @code list(Iterable)
  template <typename It>
    requires __concepts::TypedIterable<It, element>
  explicit List(It& iterable) {
    bool no_stop_iteration = true;
    auto it = iterable.Iter();

    while (no_stop_iteration) {
      try {
        Append(Next(*it));
      } catch (StopIteration) {
        no_stop_iteration = false;
        break;
      }
    }
  }

  /// @brief Creates a list with the provided variadic arguments.
  /// @code list(...)
  template <typename... Args>
  List(Args... rest) {
    (Append(std::forward<Args>(rest)), ...);
  }

  /// @brief Creates a list from an initializer list (list literal).
  /// @code [...]
  List(std::initializer_list<value_type> elements) {
    v_.reserve(elements.size());

    if constexpr (__memory::Handle<value_type>) {
      std::copy(std::make_move_iterator(elements.begin()),
                std::make_move_iterator(elements.end()),
                std::back_inserter(v_));
    } else {
      std::copy(elements.begin(), elements.end(), std::back_inserter(v_));
    }
  }

  /// @brief Generic constructor forwarding arguments to actual constructor
  /// methods.
  /// @code List.__init__()
  template <typename... Args>
  static handle Init(Args&&... args) {
    return __memory::Init<self>(std::forward<Args>(args)...);
  }

  /// @brief Appends @p elem to the end of the list.
  /// @code list.append(elem)
  void Append(__memory::ReadOnly<element> elem) { v_.emplace_back(elem); }

  /// @brief Appends variadic args @p rest to the end of the list.
  /// @code list.append(...)
  template <typename... Args>
  void Append(Args... rest) {
    (Append(std::forward<Args>(rest)), ...);
  }

  /// @brief Returns whether @p elem is in the list. O(n).
  /// @code elem in list
  __types::Bool Contains(__memory::ReadOnly<element> elem) const {
    return std::find(v_.cbegin(), v_.cend(), elem) != v_.cend();
  }

  /// @brief Clears the elements of the list.
  /// @code list.clear()
  void Clear() { v_.clear(); }

  /// @brief Creates a shallow copy of the list.
  /// @code list.copy()
  handle Copy() const {
    // Invoke copy constructor
    return Init(*this);
  }

  /// @brief Extends this list with the elements of @p other.
  /// @code list.extend(list)
  void Extend(const self& other) {
    v_.reserve(v_.size() + other.v_.size());

    std::copy(other.v_.cbegin(), other.v_.cend(), std::back_inserter(v_));
  }

  void Extend(const handle& other) { Extend(*other); }

  /// @brief Extends this list with the elements of @p other.
  /// @code list += other
  void operator+=(const self& other) { this->Extend(other); }
  void operator+=(const handle& other) { this->operator+=(*other); }

  /// @brief Concatenates this list with @p other.
  /// @code list + other
  handle operator+(const self& other) const {
    auto res = Init(*this);

    res->Extend(other);

    return res;
  }

  handle operator+(const handle& other) const { return operator+(*other); }

  /// @brief Returns a copy of this list with its elements repeated @p i times.
  /// @code list * i
  handle operator*(__types::Int i) const {
    auto res = Init();

    if (i <= 0) {
      return res;
    }

    res->v_.reserve(v_.size() * i);

    for (; i > 0; --i) {
      res->Extend(*this);
    }

    return res;
  }

  /// @brief Repeats this list's elements @p i - 1 times.
  /// @code list *= i
  void operator*=(__types::Int i) {
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
  reference operator[](__types::Int idx) {
    const auto idx_opt = TryGetNormalizedIndex(idx);

    if (!idx_opt) {
      throw IndexError("list index out of range");
    }

    return v_[*idx_opt];
  }

  const_reference operator[](__types::Int idx) const {
    const auto idx_opt = TryGetNormalizedIndex(idx);

    if (!idx_opt) {
      throw IndexError("list index out of range");
    }

    return v_[*idx_opt];
  }

  /// @brief Returns the number of elements in the list.
  /// @code len(list)
  __types::Int Len() const { return v_.size(); }

  /// @brief Returns the smallest element in the list. If the list is empty,
  /// throws ValueError.
  /// @code min(list)
  value_type Min() const {
    if (v_.empty()) {
      throw ValueError("Min() arg is an empty sequence");
    }

    if constexpr (__concepts::Object<element>) {
      return *std::min_element(
          v_.cbegin(), v_.cend(),
          [](const auto a, const auto b) { return operators::Lt(*a, *b); });
    } else {
      return *std::min_element(v_.cbegin(), v_.cend());
    }
  }

  /// @brief Returns the biggest element in the list. If the list is empty,
  /// throws ValueError.
  /// @code max(list)
  value_type Max() const {
    if (v_.empty()) {
      throw ValueError("Max() arg is an empty sequence");
    }

    if constexpr (__concepts::Object<element>) {
      return *std::max_element(
          v_.cbegin(), v_.cend(),
          [](const auto a, const auto b) { return operators::Lt(*a, *b); });
    } else {
      return *std::max_element(v_.cbegin(), v_.cend());
    }
  }

  /// @brief Returns the number of times @p elem is present in the list.
  /// @code list.count(x)
  __types::Int Count(__memory::ReadOnly<element> elem) const {
    return std::count_if(v_.cbegin(), v_.cend(),
                         [elem](__memory::ReadOnly<element> val) {
                           return operators::Eq(val, elem);
                         });
  }

  /// @brief Returns the elements in the list such that the elements' indices
  /// satify @p start <= idx < @p end, with @p step indices between the
  /// elements. If @p start >= @p end, then the returned list is empty.
  /// If @p step is negative, then the returned list is empty. If @p step is
  /// 0, then this throws ValueError.
  /// @code list[i:j:k]
  handle Slice(__types::Int start = 0,
               __types::Int end = kEndIndex,
               __types::Int step = 1) const {
    auto res = Init();

    auto slice_params_opt = TryGetNormalizedSliceParams(start, end, step);

    if (!slice_params_opt) {
      return res;
    }

    const auto size_t_start = slice_params_opt->start;
    const auto size_t_end = slice_params_opt->end;
    const auto size_t_step = slice_params_opt->step;

    // Simple range copy
    if (size_t_step == 1) {
      res->v_.reserve(size_t_end - size_t_start);

      // Need to recalculate in case reserve() invalidated the pre-calculated
      // iterators
      const auto start_it = v_.begin() + size_t_start;
      const auto end_it = v_.begin() + size_t_end;

      std::copy(start_it, end_it, std::back_inserter(res->v_));

      return res;
    }

    // Stepped range copy
    res->v_.reserve(
        GetNumberOfElementsInSlice(size_t_start, size_t_end, size_t_step));

    // Need to recalculate in case reserve() invalidated the pre-calculated
    // iterators
    const auto start_it = v_.begin() + size_t_start;
    const auto end_it = v_.begin() + size_t_end;

    size_t i = 0;

    std::copy_if(start_it, end_it, std::back_inserter(res->v_),
                 [&i, size_t_step](const auto) -> bool {
                   return i++ % size_t_step == 0;
                 });

    return res;
  }

#if __cplusplus >= 202302L
  handle operator[](__types::Int start = 0,
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
        start_it, v_.end(),
        [&i, size_t_start, size_t_end, size_t_step](const auto) -> bool {
          const auto remove =
              i + size_t_start < size_t_end && i % size_t_step == 0;
          ++i;
          return remove;
        });

    v_.erase(erase_from_it, v_.end());
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

  void ReplaceSlice(const handle& other,
                    __types::Int start = 0,
                    __types::Int end = kEndIndex,
                    __types::Int step = 1) {
    return ReplaceSlice(*other, start, end, step);
  }

  /// @brief Returns the index of @p elem in the list, starting the search from
  /// @p start. If @p elem does not exist in the list, then throws ValueError.
  /// If @p start is negative, it is clamped to 0. If @p start is greater than
  /// the last index in the list, then it throws ValueError.
  /// @code list.index(i, (j))
  __types::Int Index(__memory::ReadOnly<element> elem,
                     __types::Int start = 0) const {
    return Index(elem, start, v_.size());
  }

  /// @brief Returns the index of @p elem in the list, starting the search from
  /// @p start and ending at @p end. If @p elem does not exist in the list,
  /// then throws ValueError. If @p start or @p end are negative, they are
  /// clamped to 0. If @p start is greater than the last index in the list,
  /// then it throws ValueError. If @p end is greater than the last index in
  /// the list, it is clamped to the length of the list.
  /// @code list.index(i, j, k)
  __types::Int Index(__memory::ReadOnly<element> elem,
                     __types::Int start,
                     __types::Int end) const {
    end = ClampIndex(end);

    for (__types::Int idx = ClampIndex(start); idx < end; ++idx) {
      if (v_[idx] == elem) {
        return idx;
      }
    }

    throw ValueError("{elem} is not in list");
  }

  /// @brief Inserts @p elem so that it becomes the element at @p idx, pushing
  /// any element at that position to the right. @p idx is clamped to the
  /// length of the list.
  /// @code list.insert(idx, x)
  void Insert(__types::Int idx, value_type elem) {
    const auto size_t_idx = NormalizeOrClampIndex(idx);

    if (size_t_idx == v_.size()) {
      v_.emplace_back(elem);
    } else {
      const auto it = GetIterator(size_t_idx);
      v_.insert(it, elem);
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

    if (size_t_idx == v_.size() - 1) {
      // Trivial case, pop from the back
      v_.pop_back();
    } else {
      // Erase an element from the start or middle
      v_.erase(it);
    }

    return elem;
  }

  /// @brief Removes the first occurrence of @p elem from the list. Elements
  /// are shifted to make the list contiguous. If the list is empty or
  /// @p elem does not occur in the list, throws ValueError.
  /// @code list.remove(elem)
  void Remove(__memory::ReadOnly<element> elem) {
    if (v_.empty()) {
      throw ValueError("List.Remove(x): x not in list");
    }

    auto it = v_.end();

    if constexpr (__concepts::Object<element>) {
      it = std::find_if(v_.begin(), v_.end(),
                        [&elem](const auto v) { return elem == v; });
    } else {
      it = std::find(v_.begin(), v_.end(), elem);
    }

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

  /// @brief Sorts the list in-place, with the order of equal-comparing
  /// elements guaranteed to be preserved. Each element is compared using
  /// the less-than operator.
  /// @code sort(list, reverse)
  void Sort(__types::Bool reverse = false) {
    if (v_.empty()) {
      return;
    }

    if (reverse) {
      // We sort with the inverse of the comparison to make sure the sort
      // is stable, rather than reverse the results afterwards
      std::sort(v_.begin(), v_.end(), [](const auto a, const auto b) {
        return !(operators::Lt(a, b) || !operators::Lt(b, a));
      });
    } else {
      std::sort(v_.begin(), v_.end(),
                [](const auto a, const auto b) { return operators::Lt(a, b); });
    }
  }

  /// @brief Sorts the list in-place, with the order of equal-comparing
  /// elements guaranteed to be preserved. Every element is transformed via
  /// @p key before it is compared using the less-than operator.
  /// @code sort(list, key, reverse)
  template <typename K>
    requires details::ListSortKey<K, element>
  void Sort(const K& key, __types::Bool reverse = false) {
    if (v_.empty()) {
      return;
    }

    if (reverse) {
      // We sort with the inverse of the comparison to make sure the sort
      // is stable, rather than reverse the results afterwards
      std::sort(v_.begin(), v_.end(), [&key](const auto a, const auto b) {
        const auto ka = key(a);
        const auto kb = key(b);
        return !(operators::Lt(ka, kb) || !operators::Lt(kb, ka));
      });
    } else {
      std::sort(v_.begin(), v_.end(), [&key](const auto a, const auto b) {
        return operators::Lt(key(a), key(b));
      });
    }
  }

  /// @brief Returns an iterator to this list.
  /// @code list.__iter__()
  __memory::handle_t<Iterator<element>> Iter() {
    return details::ListIterator<element>::Init(v_.begin(), v_.end());
  }

  /// @brief Native support for C++ for..in loops.
  iterator begin() { return v_.begin(); }
  iterator end() { return v_.end(); }
  const_iterator begin() const { return v_.cbegin(); }
  const_iterator end() const { return v_.cend(); }
  const_iterator cbegin() const { return v_.cbegin(); }
  const_iterator cend() const { return v_.cend(); }

  /// @code bool(list)
  __types::Bool AsBool() const { return !v_.empty(); }

  /// @brief Implicit conversion to Bool (C++ bool) for conditionals.
  /// @code if list:
  operator __types::Bool() const { return AsBool(); }

  /// @brief Returns false all the time for all arguments so long as they are
  /// not a list of the same type of elements.
  /// @code list == other
  template <typename U>
  __types::Bool Eq(const U&) const {
    return false;
  }

  /// @brief Returns true if this and @p other contain the same elements, and
  /// false otherwise.
  /// @code list == other
  template <>
  __types::Bool Eq(const self& other) const {
    if constexpr (__concepts::Object<element>) {
      return std::equal(
          v_.begin(), v_.end(), other.v_.begin(), other.v_.end(),
          [](const auto a, const auto b) { return operators::Eq(*a, *b); });
    } else {
      return v_ == other.v_;
    }
  }

  template <>
  __types::Bool Eq(const handle& other) const {
    return Eq(*other);
  }

  /// @brief Native support for C++ == and != operators.
  template <typename U>
  bool operator==(const U& other) const {
    return Eq(other);
  }

  template <>
  bool operator==(const handle& other) const {
    return operator==(*other);
  }

  template <typename U>
  bool operator!=(const U& other) const {
    return !Eq(other);
  }

  template <>
  bool operator!=(const handle& other) const {
    return operator!=(*other);
  }

  /// @brief Returns the string representation of the list.
  /// @code str(list)
  __types::Str AsStr() const {
    std::ostringstream oss;

    oss << "[";

    if (!v_.empty()) {
      const auto last = v_.size() - 1;

      for (size_t i = 0; i < last; ++i) {
        oss << builtins::AsStr(v_[i]) << ", ";
      }

      oss << builtins::AsStr(v_[last]);
    }

    oss << "]";

    return oss.str();
  }

  /// @brief Returns the representation of the list.
  /// @code repr(list)
  __types::Str Repr() const {
    std::ostringstream oss;

    oss << "[";

    if (!v_.empty()) {
      const auto last = v_.size() - 1;

      for (size_t i = 0; i < last; ++i) {
        oss << builtins::Repr(v_[i]) << ", ";
      }

      oss << builtins::Repr(v_[last]);
    }

    oss << "]";

    return oss.str();
  }

 private:
  size_t ClampIndex(__types::Int idx) const {
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

  std::optional<size_t> TryGetNormalizedIndex(__types::Int idx) const {
    if (idx < 0) {
      idx += v_.size();
    }

    if (idx < 0 || idx >= v_.size()) {
      return std::nullopt;
    }

    return static_cast<size_t>(idx);
  }

  size_t NormalizeOrClampIndex(__types::Int idx) const {
    return TryGetNormalizedIndex(idx).value_or(ClampIndex(idx));
  }

  iterator GetIterator(size_t idx) { return v_.begin() + idx; }

  const_iterator GetIterator(size_t idx) const { return v_.cbegin() + idx; }

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

  void ReplaceSliceSingleStepExpanding(const self& other,
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

  void ReplaceSliceSingleStepReducing(const self& other,
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

  void ReplaceSliceMultiStep(const self& other,
                             SliceParams<iterator> slice_params) {
    const auto [start, end, step, start_it, end_it] = std::move(slice_params);
    const auto num_old_elems = GetNumberOfElementsInSlice(start, end, step);

    if (other.v_.size() != num_old_elems) {
      throw ValueError(
          "ValueError: attempt to assign sequence of size {} to extended "
          "slice "
          "of size {}");
    }

    size_t idx = 0;
    auto other_it = other.v_.begin();
    const auto other_end = other.v_.end();

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

  storage v_;
};

namespace details {

template <__concepts::Entity T>
class ListIterator : public Iterator<T>,
                     public std::enable_shared_from_this<ListIterator<T>> {
 public:
  /// @brief Mamba-specific
  using element = T;

  using value_type = __memory::managed_t<element>;
  using iterator = List<element>::iterator;

  /// @brief Mamba-specific
  using self = ListIterator<element>;
  using handle = __memory::handle_t<self>;

  ListIterator(iterator it, iterator end)
      : it_(std::move(it)), end_(std::move(end)) {}

  ~ListIterator() override = default;

  /// @brief Generic constructor forwarding arguments to actual constructor
  /// methods.
  /// @code ListIterator.__init__()
  template <typename... Args>
  static handle Init(Args&&... args) {
    return __memory::Init<self>(std::forward<Args>(args)...);
  }

  __memory::handle_t<Iterator<element>> Iter() override {
    return std::enable_shared_from_this<self>::shared_from_this();
  }

  value_type Next() override {
    if (it_ == end_) {
      throw StopIteration("end of iterator");
    }

    return *it_++;
  }

  __types::Str Repr() const override { return "ListIterator"; }

  bool operator==(const self& other) const {
    return it_ == other.it_ && end_ == other.end_;
  }

  bool operator==(const handle& other) const { return it_ == *other; }

  bool operator!=(const self& other) const { return !(*this == other); }
  bool operator!=(const handle& other) const { return !(*this == *other); }

 private:
  iterator it_;
  iterator end_;
};

}  // namespace details

}  // namespace mamba::builtins
