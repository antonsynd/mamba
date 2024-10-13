#pragma once

#include <algorithm>
#include <concepts>
#include <initializer_list>
#include <memory>
#include <optional>
#include <sstream>
#include <unordered_set>
#include <utility>

#include "mamba/__concepts/entity.hpp"
#include "mamba/__memory/handle.hpp"
#include "mamba/__memory/managed.hpp"
#include "mamba/__memory/read_only.hpp"
#include "mamba/builtins/__types/int.hpp"
#include "mamba/builtins/__types/str.hpp"
#include "mamba/builtins/as_str.hpp"
#include "mamba/builtins/error.hpp"
#include "mamba/builtins/iteration.hpp"
#include "mamba/builtins/repr.hpp"

namespace mamba::builtins::__types {
namespace details {

// Forward declaration
template <__concepts::Entity T>
class SetIteratorBase;

}  // namespace details

/// Curiously recurring template
template <__concepts::Entity T, typename Derived>
class SetBase : public std::enable_shared_from_this<Derived<T>> {
 public:
  /// @note Mamba-specific
  using element = T;

  using key_type = __memory::managed_t<element>;
  using value_type = key_type;
  using reference = value_type&;
  using const_reference = const value_type&;

  /// @note Mamba-specific
  using storage = std::unordered_set<value_type>;

  using iterator = storage::iterator;
  using const_iterator = storage::const_iterator;

  /// @note Mamba-specific
  using self = Derived<element>;
  using handle = __memory::handle_t<self>;

  /// @brief Creates an empty set.
  /// @code set()
  SetBase() {}

  /// @brief Creates a set from the elements in @p it. Value types
  /// are copied.
  /// @code set(Iterable)
  template <typename It>
    requires __concepts::TypedIterable<It, element>
  explicit SetBase(It& iterable) {
    bool no_stop_iteration = true;
    auto it = iterable.Iter();

    while (no_stop_iteration) {
      try {
        Add(Next(*it));
      } catch (StopIteration) {
        no_stop_iteration = false;
        break;
      }
    }
  }

  /// @brief Creates a set with the provided variadic arguments.
  /// @code set(...)
  template <typename... Args>
  SetBase(Args... rest) {
    (Add(std::forward<Args>(rest)), ...);
  }

  /// @brief Creates a set from an initializer list.
  SetBase(std::initializer_list<value_type> elements) {
    s_.reserve(elements.size());

    if constexpr (__memory::Handle<value_type>) {
      std::copy(std::make_move_iterator(elements.begin()),
                std::make_move_iterator(elements.end()),
                std::back_inserter(s_));
    } else {
      std::copy(elements.begin(), elements.end(), std::back_inserter(s_));
    }
  }

  /// @brief Returns whether @p elem is in the set. O(1).
  /// @code elem in set
  __types::Bool In(__memory::ReadOnly<element> elem) const {
    return s_.count(elem);
  }

  /// @brief Creates a shallow copy of the set.
  /// @code set.copy()
  handle Copy() const {
    // Invoke copy constructor
    return Init(*this);
  }

  /// @brief Returns the number of elements in the set.
  /// @code len(set)
  __types::Int Len() const { return s_.size(); }

  /// @code set.isdisjoint(other)
  __types::Bool IsDisjoint(const handle& other) const {
    return Intersection(other)->s_.empty();
  }

  /// @code set.issubset(other)
  template <typename It>
    requires __concepts::TypedIterable<It, element>
  __types::Bool IsSubset(It& other) const {}

  /// @code set.__lteq__(other)
  __types::Bool LtEq(const handle& other) const { return IsSubset(other); }

  /// @code set <= other
  bool operator<=(const handle& other) const { return LtEq(other); }

  /// @code set.__lt__(other)
  __types::Bool Lt(const handle& other) const {
    return LtEq(other) && !Eq(other);
  }

  /// @code set < other
  bool operator<(const handle& other) const { return Lt(other); }

  /// @code set.issuperset(other)
  template <typename It>
    requires __concepts::TypedIterable<It, element>
  __types::Bool IsSuperset(It& other) const {}

  /// @code set.__gteq__(other)
  __types::Bool GtEq(const handle& other) const { return IsSuperset(other); }

  /// @code set.__gt__(other)
  __types::Bool Gt(const handle& other) const {
    return GtEq(other) && !Eq(other);
  }

  /// @code set >= other
  bool operator>=(void other) const { return GtEq(other); }

  /// @code set > other
  bool operator>(void other) const { return Gt(other); }

  handle Union(void other) const {}
  handle operator|(void other) const { return Union(other); }

  handle Intersection(void other) const {}
  handle operator&(void other) const { return Intersection(other); }

  handle Difference(void other) const {}
  handle operator-(void other) const { return Difference(other); }

  handle SymmetricDifference(void other) const {}
  handle operator^(void other) const { return SymmetricDifference(other); }

  /// @brief Returns an iterator to this set.
  /// @code set.__iter__()
  __memory::handle_t<Iterator<element>> Iter() {
    return details::SetIteratorBase<element>::Init(s_.begin(), s_.end());
  }

  /// @brief Native support for C++ for..in loops.
  iterator begin() { return s_.begin(); }
  iterator end() { return s_.end(); }
  const_iterator begin() const { return s_.cbegin(); }
  const_iterator end() const { return s_.cend(); }
  const_iterator cbegin() const { return s_.cbegin(); }
  const_iterator cend() const { return s_.cend(); }

  /// @code bool(set)
  __types::Bool AsBool() const { return !s_.empty(); }

  /// @brief Implicit conversion to Bool (C++ bool) for conditionals.
  /// @code if set:
  operator __types::Bool() const { return AsBool(); }

  /// @brief Returns false all the time for all arguments so long as they are
  /// not a set of the same type of elements.
  /// @code set == other
  template <typename U>
  __types::Bool Eq(const U&) const {
    return false;
  }

  /// @brief Returns true if this and @p other contain the same elements, and
  /// false otherwise.
  /// @code set == other
  template <>
  __types::Bool Eq(const self& other) const {
    if constexpr (__concepts::Object<element>) {
      return std::equal(
          s_.begin(), s_.end(), other.s_.begin(), other.s_.end(),
          [](const auto a, const auto b) { return operators::Eq(*a, *b); });
    } else {
      return s_ == other.s_;
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

  /// @brief Returns the string representation of the set.
  /// @code str(set)
  virtual __types::Str AsStr() const = 0;

  /// @brief Returns the representation of the set.
  /// @code repr(set)
  virtual __types::Str Repr() const = 0;

 protected:
  /// @brief Returns the string representation of the set.
  /// @code str(set)
  __types::Str AsStrImpl(std::string_view prefix,
                         std::string_view suffix) const {
    std::ostringstream oss;

    oss << prefix;

    if (!s_.empty()) {
      const auto last = s_.size() - 1;

      for (size_t i = 0; i < last; ++i) {
        oss << builtins::AsStr(s_[i]) << ", ";
      }

      oss << builtins::AsStr(s_[last]);
    }

    oss << suffix;

    return oss.str();
  }

  /// @brief Returns the representation of the set.
  /// @code repr(set)
  __types::Str ReprImpl(std::string_view prefix,
                        std::string_view suffix) const {
    std::ostringstream oss;

    oss << prefix << "{";

    if (!s_.empty()) {
      const auto last = s_.size() - 1;

      for (size_t i = 0; i < last; ++i) {
        oss << builtins::Repr(s_[i]) << ", ";
      }

      oss << builtins::Repr(s_[last]);
    }

    oss << "}" << suffix;

    return oss.str();
  }

  std::optional<iterator> TryFind(__memory::ReadOnly<element> elem) {
    if (s_.empty()) {
      return std::nullopt;
    }

    auto it = s_.end();

    if constexpr (__concepts::Object<element>) {
      it = std::find_if(s_.begin(), s_.end(),
                        [&elem](const auto v) { return elem == v; });
    } else {
      it = std::find(s_.begin(), s_.end(), elem);
    }

    return it;
  }

  storage s_;
};

namespace details {

template <__concepts::Entity T>
class SetIteratorBase
    : public Iterator<T>,
      public std::enable_shared_from_this<SetIteratorBase<T>> {
 public:
  /// @brief Mamba-specific
  using element = T;

  using value_type = __memory::managed_t<element>;
  using iterator = SetBase<element>::iterator;

  /// @brief Mamba-specific
  using self = SetIteratorBase<element>;
  using handle = __memory::handle_t<self>;

  SetIteratorBase(iterator it, iterator end)
      : it_(std::move(it)), end_(std::move(end)) {}

  ~SetIteratorBase() override = default;

  /// @brief Generic constructor forwarding arguments to actual constructor
  /// methods.
  /// @code SetIteratorBase.__init__()
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

  __types::Str Repr() const override { return "SetIteratorBase"; }

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

}  // namespace mamba::builtins::__types
