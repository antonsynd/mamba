#pragma once

#include <algorithm>
#include <concepts>
#include <initializer_list>
#include <memory>
#include <optional>
#include <sstream>
#include <string_view>
#include <unordered_set>
#include <utility>

#include "mamba/builtins/__meta/hashable.hpp"
#include "mamba/builtins/__meta/value.hpp"
#include "mamba/builtins/__types/int.hpp"
#include "mamba/builtins/__types/long.hpp"
#include "mamba/builtins/__types/object.hpp"
#include "mamba/builtins/__types/str.hpp"
#include "mamba/builtins/__types/traits.hpp"
#include "mamba/builtins/error.hpp"
#include "mamba/builtins/iteration.hpp"
#include "mamba/builtins/operators.hpp"
#include "mamba/builtins/repr.hpp"

namespace mamba {
namespace collections::abc {
namespace details {

// Forward declaration
template <typename T>
class SetIterator;

}  // namespace details

/// Curiously recurring template
template <builtins::details::Hashable T>
class Set : virtual public Collection<T> {
 public:
  using value_type = T;

  /// @note Mamba-specific
  using self = AbstractSet<value_type>;
  using storage = std::unordered_set<value_type>;

  using key_type = value_type;
  using reference = value_type&;
  using const_reference = const value_type&;

  using iterator = storage::iterator;
  using const_iterator = storage::const_iterator;

  /// @brief Creates an empty set.
  /// @code set()
  AbstractSet() : data_(std::make_shared<Data>()) {}

  /// @brief Creates a set from the elements in @p other. Value types
  /// are copied.
  /// @code set(set)
  /// @note This is the C++ copy constructor.
  AbstractSet(const self& other) : data_(std::make_shared<Data>()) {
    std::copy(other.data_->s_.begin(), other.data->s_.end(),
              std::back_inserter(data_->s_));
  }

  /// @note Rule of 5
  AbstractSet(self&& other) : data_(std::move(other.data_)) {}
  ~AbstractSet() = default;
  self& operator=(const self& other) { data_ = other.data_; }
  self& operator=(self&& other) { data_ = std::move(other.data_); }

  /// @brief Creates a set from the elements in @p it. Value types
  /// are copied.
  /// @code set(Iterable)
  template <typename It>
    requires builtins::details::IterableOf<It, value_type>
  AbstractSet(const It& iterable) : data_(std::make_shared<Data>()) {
    for (builtins::details::Own<value_type> elem : iterable.__Iter__()) {
      Add(std::forward<value_type>(elem));
    }
  }

  /// @brief Creates a set from an initializer list.
  /// @code {...}
  AbstractSet(std::initializer_list<value_type> elements) {
    data_->s_.reserve(elements.size());

    if constexpr (builtins::details::Value<value_type>) {
      std::copy(elements.begin(), elements.end(),
                std::back_inserter(data_->s_));
    } else {
      std::copy(std::make_move_iterator(elements.begin()),
                std::make_move_iterator(elements.end()),
                std::back_inserter(data_->s_));
    }
  }

  /// @brief Returns whether @p elem is in the set. O(1).
  /// @code elem in set
  builtins::details::Bool __Contains__(
      builtins::details::Const<value_type> elem) const {
    return data_->s_.count(elem);
  }

  Str __Name__() const override {
    std::ostringstream oss;

    oss << "AbstractSet[" << builtins::details::Traits<value_type>::kName
        << "]";

    return oss.str();
  }

  /// @brief Creates a shallow copy of the set.
  /// @code set.copy()
  self Copy() const { return self(*this); }

  /// @brief Returns an iterator to this set.
  /// @code set.__iter__()
  details::SetIterator<value_type> __Iter__() const {
    return details::SetIterator<value_type>(data_->s_.begin(), data_->s_.end());
  }

  /// @brief Returns the number of elements in the set.
  /// @code len(set)
  builtins::details::Int __Len__() const { return data_->s_.size(); }

  /// @note Specialization for sets.
  self Intersection(const self& other) const {
    self res;

    std::copy_if(
        other.data_->s_.begin(), other.data_->s_.end(),
        std::back_inserter(res.data_->s_),
        [](details::Const<value_type> elem) { return __Contains__(elem); });

    return res;
  }

  template <typename It>
    requires builtins::details::IterableOf<It, value_type>
  self Intersection(const It& other) const {
    self res;

    for (builtins::details::Const<value_type> elem : other.__Iter__()) {
      if (__Contains__(elem)) {
        res.Add(elem);
      }
    }

    return res;
  }

  self operator&(const self& other) const { return Intersection(other); }

  builtins::details::Bool IsDisjoint(const self& other) const {
    return std::none_of(other.data_->s_.begin(), other.data_->s_.end(),
                        [this](builtins::details::Const<value_type> elem) {
                          return __Contains__(elem);
                        });
  }

  /// @code set.isdisjoint(other)
  template <typename It>
    requires builtins::details::IterableOf<It, value_type>
  builtins::details::Bool IsDisjoint(const It& other) const {
    for (builtins::details::Const<value_type> elem : other.__Iter__()) {
      if (__Contains__(elem)) {
        return false;
      }
    }

    return true;
  }

  builtins::details::Bool IsSubset(const self& other) const {
    // A set is always a subset of itself
    if (__Id__() == other.__Id__()) {
      return true;
    }

    // A set cannot be a subset of a smaller set
    if (__Len__() > other.__Len__()) {
      return false;
    }

    return std::all_of(data_->s_.begin(), data_->s_.end(),
                       [this](builtins::details::Const<value_type> elem) {
                         other.__Contains__(elem);
                       });
  }

  /// @code set.issubset(other)
  template <typename It>
    requires builtins::details::IterableOf<It, value_type>
  builtins::details::Bool IsSubset(const It& other) const {
    auto missing_elements = __Len__();

    for (builtins::details::Const<value_type> elem : other.__Iter__()) {
      if (__Contains__(elem)) {
        --missing_elements;
      }
    }

    // If this is a subset of other, then all of this one's elements must be
    // in other
    return missing_elements == 0;
  }

  /// @code set.__lteq__(other)
  builtins::details::Bool __LtEq__(const self& other) const {
    return IsSubset(other);
  }

  /// @code set <= other
  bool operator<=(const self& other) const { return __LtEq__(other); }

  /// @brief This determines if this set is a proper subset of @p other.
  /// @code set.__lt__(other)
  builtins::details::Bool __Lt__(const self& other) const {
    // A set is not a proper subset of itself
    if (__Id__() == other.__Id__()) {
      return false;
    }

    // A set cannot be a proper subset of a smaller or equal sized set
    if (__Len__() >= other.__Len__()) {
      return false;
    }

    // Because we eliminate the possibility of @p other being of equal length
    // to this set, then all we have to do is establish that this set's elements
    // are in @p other
    return std::all_of(data_->s_.begin(), data_->s_.end(),
                       [this](builtins::details::Const<value_type> elem) {
                         other.__Contains__(elem);
                       });
  }

  /// @code set < other
  bool operator<(const self& other) const { return __Lt__(other); }

  /// @code set.issuperset(other)
  template <typename It>
    requires builtins::details::IterableOf<It, value_type>
  builtins::details::Bool IsSuperset(const It& other) const {
    return other.__LtEq__(*this);
  }

  /// @code set.__gteq__(other)
  builtins::details::Bool __GtEq__(const self& other) const {
    return IsSuperset(other);
  }

  /// @code set.__gt__(other)
  builtins::details::Bool __Gt__(const self& other) const {
    return __GtEq__(other) && !__Eq__(other);
  }

  /// @code set >= other
  bool operator>=(const self& other) const { return GtEq(other); }

  /// @code set > other
  bool operator>(const self& other) const { return Gt(other); }

  template <typename It>
    requires builtins::details::IterableOf<It, value_type>
  self Union(const It& other) const {}
  self operator|(const self& other) const { return Union(other); }

  template <typename It>
    requires builtins::details::IterableOf<It, value_type>
  self Difference(const It& other) const {}
  self operator-(const self& other) const { return Difference(other); }

  template <typename It>
    requires builtins::details::IterableOf<It, value_type>
  self SymmetricDifference(const It& other) const {}
  self operator^(const self& other) const { return SymmetricDifference(other); }

  /// @brief Native support for C++ for..in loops.
  iterator begin() { return data_->s_.begin(); }
  iterator end() { return data_->s_.end(); }
  const_iterator begin() const { return data_->s_.cbegin(); }
  const_iterator end() const { return data_->s_.cend(); }
  const_iterator cbegin() const { return data_->s_.cbegin(); }
  const_iterator cend() const { return data_->s_.cend(); }

  /// @code bool(set)
  builtins::details::Bool __Bool__() const { return !data_->s_.empty(); }

  /// @brief Returns true if this and @p other contain the same elements, and
  /// false otherwise.
  /// @code set == other
  builtins::details::Bool __Eq__(const self& other) const {
    return std::equal(data_->s_.begin(), data_->s_.end(),
                      other.data_->s_.begin(), other.data_->s_.end(),
                      [](details::Const<value_type> a,
                         details::Const<value_type> b) { return a == b; });
  }

  /// @brief Native support for C++ == and != operators.
  bool operator==(const self& other) const { return __Eq__(other); }
  bool operator!=(const self& other) const { return !(*this == other); }

  // Bring in superclass member functions for which there are overloads here
  using builtins::details::Object::operator==;
  using builtins::details::Object::operator!=;
  using builtins::details::Object::__Eq__;

  explicit operator bool() const override { return __Len__() != 0; }

  builtins::details::Size __Id__() const override {
    return reinterpret_cast<builtins::details::Size>(data_.get());
  }

  /// @brief Returns the string representation of the set.
  /// @code str(set)
  virtual builtins::details::Str __Str__() const = 0;

  /// @brief Returns the representation of the set.
  /// @code repr(set)
  virtual builtins::details::Str __Repr__() const = 0;

 protected:
  /// @brief Returns the string representation of the set.
  /// @code str(set)
  builtins::details::Str AsStrImpl(std::string_view prefix,
                                   std::string_view suffix) const {
    std::ostringstream oss;

    oss << prefix;

    if (!data_->s_.empty()) {
      const auto last = data_->s_.size() - 1;

      for (size_t i = 0; i < last; ++i) {
        oss << builtins::AsStr(data_->s_[i]) << ", ";
      }

      oss << builtins::AsStr(data_->s_[last]);
    }

    oss << suffix;

    return oss.str();
  }

  /// @brief Returns the representation of the set.
  /// @code repr(set)
  builtins::details::Str ReprImpl(std::string_view prefix,
                                  std::string_view suffix) const {
    std::ostringstream oss;

    oss << prefix << "{";

    if (!data_->s_.empty()) {
      const auto last = data_->s_.size() - 1;

      for (size_t i = 0; i < last; ++i) {
        oss << builtins::Repr(data_->s_[i]) << ", ";
      }

      oss << builtins::Repr(data_->s_[last]);
    }

    oss << "}" << suffix;

    return oss.str();
  }

  void Add(value_type&& elem) {
    data_->s_.emplace_back(std::forward<value_type>(elem));
  }

  std::optional<iterator> TryFind(
      builtins::details::Const<value_type> elem) const {
    if (data_->s_.empty()) {
      return std::nullopt;
    }

    return std::find_if(
        data_->s_.begin(), data_->s_.end(),
        [&elem](builtins::details::Const<value_type> v) { return elem == v; });
  }

  std::shared_ptr<Data> Data_() { return data_; }

 private:
  class Data {
   public:
    storage data_->s_;
  };

  std::shared_ptr<Data> data_;
};

}  // namespace collections::abc

namespace builtins::details {

template <typename T>
struct Traits<collections::abc::AbstractSet<T>> {
  static constexpr std::string_view kName = "AbstractSet";
};

}  // namespace builtins::details

namespace collections::abc::details {

template <typename T>
class SetIterator : public Iterator<T> {
 public:
  using value_type = T;
  using iterator = AbstractSet<value_type>::iterator;

  /// @brief Mamba-specific
  using self = SetIterator<value_type>;
  using base = Iterator<value_type>;

  SetIterator(iterator it, iterator end)
      : base(std::move(it), std::move(end)) {}

  ~SetIterator() override = default;

  /// @brief Generic constructor forwarding arguments to actual constructor
  /// methods.
  /// @code ListIterator.__init__()
  template <typename... Args>
  static self __Init__(Args&&... args) {
    return self(std::forward<Args>(args)...);
  }

  Str __Name__() const override {
    std::ostringstream oss;

    oss << "SetIterator[" << builtins::details::Traits<value_type>::kName
        << "]";

    return oss.str();
  }
};

}  // namespace collections::abc::details

namespace builtins::details {

template <typename T>
struct Traits<collections::abc::details::SetIterator<T>> {
  static constexpr std::string_view kName = "SetIterator";
};

}  // namespace builtins::details
}  // namespace mamba
