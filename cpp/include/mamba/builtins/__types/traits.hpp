#pragma once

// #include "mamba/builtins/__concepts/value.hpp"

namespace mamba::builtins::details {

// template <Value T>
template <typename T>
struct Traits {
  static_assert(false, "Traits unimplemented");
};

// template <NotValue T>
// struct Traits {
//  public:
//   using value_type = T;

//   struct ObjectDelegate {
//    public:
//     static inline Str __Name__(const value_type& v) { return v.__Name__(); }
//     static inline Str __Repr__(const value_type& v) { return v.__Repr__(); };
//     static inline Str __Str__(const value_type& v) { return __Repr__(v); }
//     static inline Bool __Bool__(const value_type& v) { return v.__Bool__(); }
//     static inline BigInt __Id__(const value_type& v) { return v.__Id__(); }
//     static inline Bool __Eq__(const value_type& lhs, const value_type& rhs) {
//       return lhs.__Eq__(rhs);
//     }
//   };
// };

}  // namespace mamba::builtins::details
