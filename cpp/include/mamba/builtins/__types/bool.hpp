#pragma once

#include <string_view>

#include "mamba/builtins/__types/traits.hpp"

namespace mamba::builtins::details {

/// @note This goes against the Python specification which says bool is an
/// integer. This is to ensure we can write separate builtin functions for
/// Int and Bool.
using Bool = bool;

// struct BoolDelegate {
//  public:
//   using value_type = Bool;

//   static inline Str __Name__(const value_type) { return "bool"; }

//   static inline Str __Repr__(const value_type v) {
//     return v ? "True" : "False";
//   };

//   static inline Str __Str__(const value_type v) { return __Repr__(v); }

//   static inline Bool __Bool__(const value_type v) { return v; }

//   static inline Bool __Eq__(const value_type lhs, const value_type rhs) {
//     return lhs == rhs;
//   }

//   static inline BigInt __Id__(const value_type) { return -1; }
// };

// template <Bool>
template <>
struct Traits<Bool> {
  // using delegate_type = BoolDelegate;
  static constexpr std::string_view kName = "bool";
};

}  // namespace mamba::builtins::details

// IWYU pragma: private
