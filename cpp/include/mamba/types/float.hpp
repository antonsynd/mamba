#pragma once

#if __cplusplus >= 202302L
#include <stdfloat>
#endif  // __cplusplus >= 202302L

namespace mamba::builtins::types {

#if __cplusplus >= 202302L
using Float = std::float64_t;
#else   // __cplusplus >= 202302L
using Float = double;
#endif  // __cplusplus >= 202302L

}  // namespace mamba::builtins::types
