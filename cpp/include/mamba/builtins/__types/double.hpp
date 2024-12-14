#pragma once

#if __cplusplus >= 202302L
#include <stdfloat>
#endif  // __cplusplus >= 202302L

namespace mamba::builtins::details {

#if __cplusplus >= 202302L
using Double = std::float64_t;
#else   // __cplusplus >= 202302L
using Double = double;
#endif  // __cplusplus >= 202302L

}  // namespace mamba::builtins::details

// IWYU pragma: private
