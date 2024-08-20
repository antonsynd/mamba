#pragma once

namespace mamba::builtins::concepts {

template <typename T>
concept HasValueType = requires { typename T::value; };

template <typename T>
concept HasElementType = requires { typename T::element_type; };

}  // namespace mamba::builtins::concepts
