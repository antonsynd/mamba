#pragma once

namespace mamba::builtins::concepts {

template <typename T>
concept HasValueType = requires { typename T::value; };

}  // namespace mamba::builtins::concepts
