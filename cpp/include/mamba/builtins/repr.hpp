#pragma once

#include "mamba/builtins/__types/big_int.hpp"
#include "mamba/builtins/__types/bool.hpp"
#include "mamba/builtins/__types/complex.hpp"
#include "mamba/builtins/__types/double.hpp"
#include "mamba/builtins/__types/float.hpp"
#include "mamba/builtins/__types/int.hpp"
#include "mamba/builtins/__types/none.hpp"
#include "mamba/builtins/__types/object.hpp"
#include "mamba/builtins/__types/str.hpp"

namespace mamba::builtins {

details::Str Repr(const details::BigInt i);
details::Str Repr(const details::Bool b);
details::Str Repr(const details::Complex& c);
details::Str Repr(const details::Double d);
details::Str Repr(const details::Float f);
details::Str Repr(const details::Int i);
details::Str Repr(const details::None);
details::Str Repr(const details::Object& t);

}  // namespace mamba::builtins
