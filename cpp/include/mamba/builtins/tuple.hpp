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

// Concept to check if all types are the same
template <typename T, typename... Args>
concept Homogenous = (std::same_as<T, Args> && ...);

// Concept to check if types are different (not all the same)
// template <typename... Args>
// concept Heterogeneous = !Homogenous<Args...>;

// Forward declaration
template <__concepts::Entity T>
class TupleIterator;

}  // namespace details

// template <typename... Args>
//   requires details::Heterogeneous<Args...>
// class Tuple {
//  public:
//   __types::Bool Contains(elem) const;
//   __types::Int Len() const;

//  private:
// };

// Could be base class of List<T>
template <typename T, typename... Elems>
  requires details::Homogenous<T, Elems...> && __concepts::Entity<T> &&
           __concepts::LessThanComparable<T>
class Tuple : public std::enable_shared_from_this<Tuple<T>> {
 public:
  /// @note Mamba-specific
  using element = T;

  using value = __memory::managed_t<element>;
  using reference = value&;
  using const_reference = const value&;

  /// @note Mamba-specific
  using storage = std::vector<value>;

  using iterator = storage::iterator;
  using const_iterator = storage::const_iterator;

  /// @note Mamba-specific
  using self = Tuple<element>;
  using handle = __memory::handle_t<self>;

  static constexpr auto kEndIndex = std::numeric_limits<__types::Int>::min();

  /// @brief Creates an empty tuple.
  /// @code tuple()
  Tuple() {}

  /// @brief Creates a tuple with the same elements as @p it. Value types
  /// are copied.
  /// @code tuple(Iterable)
  template <typename It>
    requires __concepts::TypedIterable<It, element>
  explicit Tuple(It& iterable) {
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

  /// @brief Creates a tuple with the provided variadic arguments.
  /// @code tuple(...)
  template <typename... Args>
  Tuple(Args... rest) {
    (Append(std::forward<Args>(rest)), ...);
  }

  /// @brief Creates a tuple from an initializer tuple (tuple literal).
  /// @code ()...)
  Tuple(std::initializer_list<value> elements) {
    v_.reserve(elements.size());

    if constexpr (__memory::Handle<value>) {
      std::copy(std::make_move_iterator(elements.begin()),
                std::make_move_iterator(elements.end()),
                std::back_inserter(v_));
    } else {
      std::copy(elements.begin(), elements.end(), std::back_inserter(v_));
    }
  }

  /// @brief Generic constructor forwarding arguments to actual constructor
  /// methods.
  /// @code Tuple.__init__()
  template <typename... Args>
  static handle Init(Args&&... args) {
    return __memory::Init<self>(std::forward<Args>(args)...);
  }

  /// @brief Returns whether @p elem is in the tuple. O(n).
  /// @code elem in tuple
  __types::Bool Contains(__memory::ReadOnly<element> elem) const {
    return std::find(v_.cbegin(), v_.cend(), elem) != v_.cend();
  }

  /// @brief Creates a shallow copy of the tuple.
  /// @code tuple.copy()
  handle Copy() const {
    // Invoke copy constructor
    return Init(*this);
  }

  /// @brief Concatenates this tuple with @p other.
  /// @code tuple + other
  handle operator+(const self& other) const {
    auto res = Init(*this);

    res->Extend(other);

    return res;
  }

  handle operator+(const handle& other) const { return operator+(*other); }

  /// @brief Returns a copy of this tuple with its elements repeated @p i times.
  /// @code tuple * i
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

  const_reference operator[](__types::Int idx) const {
    const auto idx_opt = TryGetNormalizedIndex(idx);

    if (!idx_opt) {
      throw IndexError("tuple index out of range");
    }

    return v_[*idx_opt];
  }

  /// @brief Returns the number of elements in the tuple.
  /// @code len(tuple)
  __types::Int Len() const { return v_.size(); }

  /// @brief Returns the smallest element in the tuple. If the tuple is empty,
  /// throws ValueError.
  /// @code min(tuple)
  value Min() const {
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

  /// @brief Returns the biggest element in the tuple. If the tuple is empty,
  /// throws ValueError.
  /// @code max(tuple)
  value Max() const {
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

  /// @brief Returns the number of times @p elem is present in the tuple.
  /// @code tuple.count(x)
  __types::Int Count(__memory::ReadOnly<element> elem) const {
    return std::count_if(v_.cbegin(), v_.cend(),
                         [elem](__memory::ReadOnly<element> val) {
                           return operators::Eq(val, elem);
                         });
  }

  /// @brief Returns the elements in the tuple such that the elements' indices
  /// satify @p start <= idx < @p end, with @p step indices between the
  /// elements. If @p start >= @p end, then the returned tuple is empty.
  /// If @p step is negative, then the returned tuple is empty. If @p step is
  /// 0, then this throws ValueError.
  /// @code tuple[i:j:k]
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

  /// @brief Returns the index of @p elem in the tuple, starting the search from
  /// @p start. If @p elem does not exist in the tuple, then throws ValueError.
  /// If @p start is negative, it is clamped to 0. If @p start is greater than
  /// the last index in the tuple, then it throws ValueError.
  /// @code tuple.index(i, (j))
  __types::Int Index(__memory::ReadOnly<element> elem,
                     __types::Int start = 0) const {
    return Index(elem, start, v_.size());
  }

  /// @brief Returns the index of @p elem in the tuple, starting the search from
  /// @p start and ending at @p end. If @p elem does not exist in the tuple,
  /// then throws ValueError. If @p start or @p end are negative, they are
  /// clamped to 0. If @p start is greater than the last index in the tuple,
  /// then it throws ValueError. If @p end is greater than the last index in
  /// the tuple, it is clamped to the length of the tuple.
  /// @code tuple.index(i, j, k)
  __types::Int Index(__memory::ReadOnly<element> elem,
                     __types::Int start,
                     __types::Int end) const {
    end = ClampIndex(end);

    for (__types::Int idx = ClampIndex(start); idx < end; ++idx) {
      if (v_[idx] == elem) {
        return idx;
      }
    }

    throw ValueError("{elem} is not in tuple");
  }

  /// @brief Returns an iterator to this tuple.
  /// @code tuple.__iter__()
  __memory::handle_t<Iterator<element>> Iter() {
    return details::TupleIterator<element>::Init(v_.begin(), v_.end());
  }

  /// @brief Native support for C++ for..in loops.
  iterator begin() { return v_.begin(); }
  iterator end() { return v_.end(); }
  const_iterator begin() const { return v_.cbegin(); }
  const_iterator end() const { return v_.cend(); }
  const_iterator cbegin() const { return v_.cbegin(); }
  const_iterator cend() const { return v_.cend(); }

  /// @code bool(tuple)
  __types::Bool AsBool() const { return !v_.empty(); }

  /// @brief Implicit conversion to Bool (C++ bool) for conditionals.
  /// @code if tuple:
  operator __types::Bool() const { return AsBool(); }

  /// @brief Returns false all the time for all arguments so long as they are
  /// not a tuple of the same type of elements.
  /// @code tuple == other
  template <typename U>
  __types::Bool Eq(const U&) const {
    return false;
  }

  /// @brief Returns true if this and @p other contain the same elements, and
  /// false otherwise.
  /// @code tuple == other
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

  /// @brief Returns the string representation of the tuple.
  /// @code str(tuple)
  __types::Str AsStr() const {
    std::ostringstream oss;

    oss << "(";

    if (!v_.empty()) {
      const auto last = v_.size() - 1;

      for (size_t i = 0; i < last; ++i) {
        oss << builtins::AsStr(v_[i]) << ", ";
      }

      oss << builtins::AsStr(v_[last]);
    }

    oss << ")";

    return oss.str();
  }

  /// @brief Returns the representation of the tuple.
  /// @code repr(tuple)
  __types::Str Repr() const {
    std::ostringstream oss;

    oss << "(";

    if (!v_.empty()) {
      const auto last = v_.size() - 1;

      for (size_t i = 0; i < last; ++i) {
        oss << builtins::Repr(v_[i]) << ", ";
      }

      oss << builtins::Repr(v_[last]);
    }

    oss << ")";

    return oss.str();
  }

 private:
  /// @brief Appends @p elem to the end of the tuple.
  /// @code tuple.append(elem)
  void Append(__memory::ReadOnly<element> elem) { v_.emplace_back(elem); }

  /// @brief Appends variadic args @p rest to the end of the tuple.
  /// @code tuple.append(...)
  template <typename... Args>
  void Append(Args... rest) {
    (Append(std::forward<Args>(rest)), ...);
  }

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

  storage v_;
};

namespace details {

template <__concepts::Entity T>
class TupleIterator : public Iterator<T>,
                      public std::enable_shared_from_this<TupleIterator<T>> {
 public:
  using element = T;

  using value = __memory::managed_t<element>;

  using iterator = Tuple<element>::iterator;
  using const_iterator = Tuple<element>::const_iterator;

  using self = TupleIterator<element>;
  using handle = __memory::handle_t<self>;

  TupleIterator(iterator it, iterator end)
      : it_(std::move(it)), end_(std::move(end)) {}

  ~TupleIterator() override = default;

  /// @brief Generic constructor forwarding arguments to actual constructor
  /// methods.
  /// @code TupleIterator.__init__()
  template <typename... Args>
  static handle Init(Args&&... args) {
    return __memory::Init<self>(std::forward<Args>(args)...);
  }

  __memory::handle_t<Iterator<element>> Iter() override {
    return std::enable_shared_from_this<self>::shared_from_this();
  }

  value Next() override {
    if (it_ == end_) {
      throw StopIteration("end of iterator");
    }

    return *it_++;
  }

  __types::Str Repr() const override { return "TupleIterator"; }

  // Native support for C++ for..each loops
  iterator begin() { return it_; }
  iterator end() { return end_; }
  const_iterator begin() const { return it_; }
  const_iterator end() const { return end_; }
  const_iterator cbegin() const { return it_; }
  const_iterator cend() const { return end_; }

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
