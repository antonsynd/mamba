#pragma once

#include <memory>
#include <optional>
#include <unordered_map>

#include "mamba/concepts/entity.hpp"
#include "mamba/error.hpp"
#include "mamba/list.hpp"
#include "mamba/types/int.hpp"

namespace mamba::builtins {

template <concepts::Entity K, concepts::Entity V>
class Dict : public std::enable_shared_from_this<Dict<K, V>> {
 public:
  using key_type = K;
  using mapped_type = V;
  using value_type = std::pair<const key_type, mapped_type>;
  using reference = value_type&;
  using const_reference = const value&;

  /// @brief Creates an empty dict.
  /// @code dict()
  Dict() {}

  template <concepts::Mapping T>
  Dict(const Mapping& mapping) {}

  /// class dict(**kwargs)
  /// class dict(mapping, **kwargs)
  /// class dict(iterable, **kwargs)

  List<K> AsList() {}

  types::Int Len() const { return m_.size(); }

  mapped_type& operator[](const K& key) {
    auto it = m_.find(key);

    if (it == m_.end()) {
      // In this base class, it is expected to throw
      return Missing(key);
    }

    return it->second;
  }

  const mapped_type& operator[](const K& key) const {
    auto it = m_.find(key);

    if (it == m_.end()) {
      // In this base class, it is expected to throw
      return Missing(key);
    }

    return it->second;
  }

  // TODO: make generic access, if K is Handle, then const K&, else K
  virtual mapped_type Missing(const K& key) { throw ValueError(""); }

  void DeleteKey(const K& key) {
    auto it = m_.find(key);

    if (it == m_.end()) {
      // In this base class, it is expected to throw
      return Missing(key);
    }
  }

  types::Bool In(K key) const {}

  // Iter()

  /// @brief Clears the elements of the dict.
  /// @code dict.clear()
  void Clear() { m_.clear(); }

  /// @brief Creates a shallow copy of the dict.
  /// @code dict.copy()
  memory::Handle<Dict<K, V>> Copy() const {
    return memory::Init<Dict<K, V>>(*this);
  }

  // static FromKeys();

  mapped_type Get(const K& key, V default_value) {
    auto it = m_.find(key);

    if (it == m_.end()) {
      return default_value;
    }

    return it->second;
  }

  // Items()

  // Pop()

  // PopItem()

  // Reversed()

  // SetDefault(key, default)

  void Update(const Dict<K, V>& other) {
    //
  }

  // Values()

  memory::Handle<Dict<K, V>> operator|(const Dict<K, V>& other) const {
    auto res = memory::Init<Dict<K, V>>(*this);
    res.Update(other);
    return res;
  }

  void operator|=(const Dict<K, V>& other) { Update(other); }

  /// @brief Returns the string representation of the dict.
  /// @code str(dict)
  types::Str AsStr() const {
    std::ostringstream oss;

    oss << "{";

    if (!m_.empty()) {
      const auto last = v_.size() - 1;
      auto it = v_.begin();

      for (size_t i = 0; i < last; ++i, ++it) {
        oss << builtins::AsStr(it->first) << ": " << builtins::AsStr(it->second)
            << ", ";
      }

      oss << builtins::AsStr(it->first) << ": " << builtins::AsStr(it->second);
    }

    oss << "}";

    return oss.str();
  }

  /// @brief Returns the representation of the dict.
  /// @code repr(dict)
  types::Str Repr() const {
    std::ostringstream oss;

    oss << "{";

    if (!m_.empty()) {
      const auto last = v_.size() - 1;
      auto it = v_.begin();

      for (size_t i = 0; i < last; ++i, ++it) {
        oss << builtins::AsStr(it->first) << ": " << builtins::AsStr(it->second)
            << ", ";
      }

      oss << builtins::AsStr(it->first) << ": " << builtins::AsStr(it->second);
    }

    oss << "}";

    return oss.str();
  }

 private:
  std::unordered_map<K, V> m_;
};

namespace details {

class DictionaryView {};

}  // namespace details

}  // namespace mamba::builtins
