#pragma once

#if __cplusplus >= 202302L
#include <stdfloat>
#endif  // __cplusplus >= 202302L

namespace mamba::builtins {

#if __cplusplus >= 202302L
using float_t = std::float64_t;
#else   // __cplusplus >= 202302L
using float_t = double;
#endif  // __cplusplus >= 202302L

}  // namespace mamba::builtins
